#pragma once

#include <iostream>
#include <memory_resource>
#include <vector>
#include <list>

class CustomMemoryResource : public std::pmr::memory_resource {
    struct Block {
        size_t offset;
        size_t size;
        bool free;
    };

    static constexpr size_t max_size = 1024;

    char buffer[max_size];
    std::list<Block> blocks;

protected:
    void *do_allocate(size_t bytes, size_t alignment) override {
        for (auto &[offset, size, free]: blocks) {
            if (free && size >= bytes) {
                free = false;
                return buffer + offset;
            }
        }

        size_t offset = 0;
        if (!blocks.empty()) {
            const auto &last_block = blocks.back();
            offset = last_block.offset + last_block.size;
        }

        if (offset + bytes > max_size) { throw std::bad_alloc(); }

        blocks.push_back({offset, bytes, false});
        return buffer + offset;
    };

    void do_deallocate(void *ptr, size_t bytes, size_t alignment) override {
        auto offset = static_cast<char *>(ptr) - buffer;

        for (Block &b: blocks)
            if (b.offset == offset && b.size == bytes && !b.free) {
                b.free = true;
                return;
            }

        throw std::logic_error("Pointer wasn't allocated.");
    };

    bool do_is_equal(const memory_resource &other) const noexcept override {
        return this == &other;
    };

public:
    ~CustomMemoryResource() override {
        for (auto &block: blocks) { block.free = true; }
    };
};