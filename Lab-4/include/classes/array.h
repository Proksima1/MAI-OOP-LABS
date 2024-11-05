#pragma once

#include "stdlib.h"
#include "memory"
#include "iostream"

#include "exceptions.h"

template<class T>
class Array {
private:
    std::shared_ptr<T[]> _elements;
    size_t _capacity;

private:
    void _resize(size_t capacity);

public:
    size_t size;

public:
    Array();

    Array(int size);

    Array(std::initializer_list<T> t);

    Array(const Array &other);

    Array(Array &&other) noexcept;

    Array &operator=(const Array &other);

    Array &operator=(Array &&other) noexcept;

    int getCapacity() { return _capacity; }

    T operator[](int index);

    void push_back(T element);

    bool operator==(Array &other);

    bool operator!=(Array &other);

    void remove(size_t index);

};


template<class T>
Array<T>::Array() {
    _capacity = 0;
    size = 0;
    _elements = std::shared_ptr<T[]>(new T[_capacity], std::default_delete<T[]>());
}

template<class T>
Array<T>::Array(int size) {
    _capacity = size;
    this->size = 0;
    _elements = std::shared_ptr<T[]>(new T[_capacity], std::default_delete<T[]>());
}

template<class T>
Array<T>::Array(std::initializer_list<T> t) {
    _capacity = size = t.size();
    _elements = std::shared_ptr<T[]>(new T[_capacity],
                                     std::default_delete<T[]>());

    int i = 0;
    for (auto elem: t) {
        _elements[i] = std::move(elem);
        ++i;
    }
}

template<class T>
Array<T>::Array(const Array &other) {
    _capacity = other._capacity;
    size = other.size;
    _elements = std::shared_ptr<T[]>(new T[_capacity],
                                     std::default_delete<T[]>());
    for (int i = 0; i < size; ++i) {
        _elements[i] = other._elements[i];
    }
}

template<class T>
Array<T>::Array(Array &&other) noexcept {
    _elements = other._elements;
    _capacity = other._capacity;
    size = other.size;
    other._elements = nullptr;
    other._capacity = other.size = 0;
}

template<class T>
Array<T> &Array<T>::operator=(const Array &other) {
    if (this != &other) {
        _capacity = other._capacity;
        size = other.size;
        _elements = std::shared_ptr<T[]>(new T[_capacity],
                                         std::default_delete<T[]>());
        for (int i = 0; i < size; ++i)
            _elements[i] = other._elements[i];
    }
    return *this;
}

template<class T>
Array<T> &Array<T>::operator=(Array &&other) noexcept {
    if (this != &other) {
        _elements = other._elements;
        _capacity = other._capacity;
        size = other.size;

        other._elements = nullptr;
        other._capacity = other.size = 0;
    }
    return *this;
}

template<class T>
T Array<T>::operator[](int index) {
    if (index < 0) {
        return _elements[index + size];
    }
    return _elements[index];
}

template<class T>
void Array<T>::_resize(size_t capacity) {
    _capacity = capacity;
    auto temp = std::shared_ptr<T[]>(new T[_capacity],
                                     std::default_delete<T[]>());

    for (int i = 0; i < size; ++i) {
        temp[i] = std::move(_elements[i]);
    }

    _elements = temp;
}

template<class T>
void Array<T>::push_back(T element) {
    if (_capacity == size) {
        _resize(_capacity * 2 + 1);
    }

    _elements[size] = element;
    ++size;
}

template<class T>
bool Array<T>::operator==(Array &other) {
    if (other.size == size) {
        for (int i = 0; i < size; ++i) {
            if (_elements[i] != other[i])
                return false;
        }
        return true;
    }
    return false;
}

template<class T>
bool Array<T>::operator!=(Array &other) {
    return !(*this == other) ? true : false;
}


template<class T>
void Array<T>::remove(size_t index) {
    for (size_t i = index + 1; i < size; ++i)
        _elements[i - 1] = _elements[i];
    --size;
}