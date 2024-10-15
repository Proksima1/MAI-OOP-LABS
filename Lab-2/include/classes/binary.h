#ifndef OOP_LABS_BINARY_H
#define OOP_LABS_BINARY_H

#include "iostream"

class Binary {
public:
    Binary();

    Binary(const size_t &size, unsigned char value);

    Binary(const std::initializer_list<unsigned char> &data);

    Binary(const std::string &t);

    Binary(const Binary &other);

    Binary(Binary &&other) noexcept;

    Binary &operator=(const Binary &right);

    Binary &operator+=(const Binary &right);

    Binary &operator-=(const Binary &right);

    bool operator>(const Binary &right) const;

    bool operator<(const Binary &right) const;

    bool operator==(const Binary &right) const;

    unsigned char *getData();

    size_t getSize() const;

    virtual ~Binary() noexcept;

private:
    size_t _size;
    unsigned char *_data;

    void validateBit(unsigned char value);
};


#endif
