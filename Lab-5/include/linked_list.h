#pragma once
#include "memory_resource"
#include <memory>
#include <iterator>

template<class T>
class LinkedList {
private:
    typedef struct _node {
        T data;
        _node *next;

        _node(T value) : data(value), next(nullptr) {}

        _node(T value, _node *next) : data(value), next(next) {}
    } Node;

    using allocator = std::pmr::polymorphic_allocator<Node>;

    Node *_head = nullptr;
    Node *_tail = nullptr;
    allocator _alloc;
    size_t _size;


public:
    class ConstIterator {
        friend LinkedList;
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using pointer_type = const T *;
        using reference_type = const T &;

    private:
        const Node *_current;

    public:
        explicit ConstIterator(const Node *node);

        reference_type operator*() const;

        pointer_type operator->() const;

        ConstIterator &operator++();

        ConstIterator operator++(int);

        bool operator==(const ConstIterator &other) const;

        bool operator!=(const ConstIterator &other) const;
    };

    LinkedList(std::pmr::memory_resource *resource);

    virtual ~LinkedList() noexcept;

    void push_front(T element);

    void push_back(T element);

    void remove(T value);

    size_t size() const;

    bool empty() const;

    void clear();

    template<class U>
    friend std::ostream &operator<<(std::ostream &os, const LinkedList<U> &list);

    ConstIterator begin() const;

    ConstIterator end() const;
};


template<class T>
LinkedList<T>::LinkedList(std::pmr::memory_resource *resource) : _alloc(resource), _size(0) {}


template<class T>
LinkedList<T>::~LinkedList() noexcept {
    clear();
}


template<class T>
void LinkedList<T>::push_front(T element) {
    Node *new_node = _alloc.allocate(1);
    std::allocator_traits<allocator>::construct(_alloc, new_node, Node{element, _head});
    _head = new_node;
    if (_tail == nullptr) {
        _tail = new_node;
    }
    ++_size;
}

template<class T>
void LinkedList<T>::push_back(T element) {
    Node *new_node = _alloc.allocate(1);
    std::allocator_traits<allocator>::construct(_alloc, new_node, Node{element});
    if (_tail) {
        _tail->next = new_node;
        _tail = new_node;
    } else {
        _head = _tail = new_node;
    }
    ++_size;
}

template<class T>
void LinkedList<T>::remove(T value) {
    Node *current = _head;
    Node *previous = nullptr;

    while (current != nullptr) {
        if (current->data == value) {
            if (previous) {
                previous->next = current->next;
            } else {
                _head = current->next;
            }
            if (current == _tail) {
                _tail = previous;
            }
            current->~Node();
            std::allocator_traits<allocator>::destroy(_alloc, current);
            _alloc.deallocate(current, 1);
            --_size;
            return;
        }
        previous = current;
        current = current->next;
    }
}


template<class T>
size_t LinkedList<T>::size() const {
    return _size;
}

template<class T>
bool LinkedList<T>::empty() const {
    return _size == 0;
}

template<class T>
void LinkedList<T>::clear() {
    while (_head != _tail) {
        Node *temp = _head;
        _head = _head->next;
        std::allocator_traits<allocator>::destroy(_alloc, temp);
        _alloc.deallocate(temp, 1);
        --_size;
    }
}

template<class T>
std::ostream &operator<<(std::ostream &os, const LinkedList<T> &list) {
    os << 'List(';
    if (!list.empty()) {
        auto *elem = list._head;
        while (elem->next) {
            os << elem->data << "->";
            elem = elem->next;
        }
        os << elem->data;
    }
    os << ')';
    return os;
}

template<class T>
LinkedList<T>::ConstIterator::ConstIterator(const Node *node) : _current(node) {}

template<class T>
const T &LinkedList<T>::ConstIterator::operator*() const {
    return _current->data;
}

template<class T>
const T *LinkedList<T>::ConstIterator::operator->() const {
    return &(_current->data);
}

template<class T>
typename LinkedList<T>::ConstIterator &LinkedList<T>::ConstIterator::operator++() {
    _current = _current->next;
    return *this;
}

template<class T>
typename LinkedList<T>::ConstIterator LinkedList<T>::ConstIterator::operator++(int) {
    ConstIterator temp = *this;
    ++(*this);
    return temp;
}

template<class T>
bool LinkedList<T>::ConstIterator::operator==(const ConstIterator &other) const {
    return _current == other._current;
}

template<class T>
bool LinkedList<T>::ConstIterator::operator!=(const ConstIterator &other) const {
    return _current != other._current;
}

template<class T>
typename LinkedList<T>::ConstIterator LinkedList<T>::begin() const {
    return ConstIterator(_head);
}

template<class T>
typename LinkedList<T>::ConstIterator LinkedList<T>::end() const {
    return ConstIterator(nullptr);
}