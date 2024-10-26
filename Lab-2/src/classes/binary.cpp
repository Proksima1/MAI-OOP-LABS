#include "classes/binary.h"
#include "string"
#include "stdexcept"

Binary::Binary() : _size{0}, _data{nullptr} {}

Binary::Binary(const size_t &size, unsigned char value) {
    validateBit(value);
    _size = size;
    _data = new unsigned char[size];
    for (int i = 0; i < size; ++i) {
        _data[i] = value;
    }

}

Binary::Binary(const std::initializer_list<unsigned char> &data) {
    _size = data.size();
    _data = new unsigned char[_size];
    size_t pos = 0;
    for (unsigned char i: data) {
        validateBit(i);
        _data[++pos] = i;
    }
}

Binary::Binary(const std::string &data) {
    _size = data.size();
    _data = new unsigned char[_size];
    for (size_t i = 0; i < _size; i++)
    {
        validateBit(data[i]);
        _data[i] = data[i];
    }
}

Binary::Binary(const Binary &other) {
    _size = other._size;
    _data = other._data;
}

Binary::Binary(Binary &&other) noexcept {
    _size = other._size;
    _data = other._data;
    other._data = nullptr;
    other._size = 0;
}


Binary::~Binary() noexcept {
    delete[] _data;
}


void Binary::validateBit(unsigned char value) {
    if (value != '0' && value != '1') {
        throw std::invalid_argument("Bits in number must be binary");
    }
}

bool Binary::operator>(const Binary &right) const {
    if (_size > right._size)
    {
        return false;
    }

    if (_size < right._size)
    {
        return true;
    }

    for (size_t i = 0; i < _size; i++)
    {
        if (_data[i] > right._data[i])
        {
            return true;
        }
        if (_data[i] < right._data[i])
        {
            return false;
        }
    }
    return false;
}

bool Binary::operator<(const Binary &right) const {
    return right.operator>(*this);
}

bool Binary::operator==(const Binary &right) const {
    return !(*this > right || right > *this);
}

Binary &Binary::operator=(const Binary &right) {
    if (&right == this) {
        return *this;
    }
    _size = right._size;
    delete[] _data;
    _data = new unsigned char[_size];
    for (int i = 0; i < _size; ++i) {
        _data[i] = right._data[i];
    }
    return *this;
}

Binary &Binary::operator+=(const Binary &other) {
    int thisNumber = 0;
    for (size_t i = 0; i < _size; ++i) {
        thisNumber = (thisNumber << 1) | (_data[i] - '0');
    }

    int otherNumber = 0;
    for (size_t j = 0; j < other._size; ++j) {
        otherNumber = (otherNumber << 1) | (other._data[j] - '0');
    }

    int sumNumber = thisNumber + otherNumber;

    size_t newSize = 0;
    unsigned char *newData = new unsigned char[sizeof(sumNumber) * 8 + 1]{0};

    while (sumNumber > 0) {
        newData[newSize++] = (sumNumber % 2) + '0';
        sumNumber /= 2;
    }

    for (size_t i = 0; i < newSize / 2; ++i) {
        std::swap(newData[i], newData[newSize - 1 - i]);
    }

    delete[] _data;
    _data = newData;
    _size = newSize;

    return *this;
}

Binary &Binary::operator-=(const Binary &other) {
    if (_size < other._size) {
        throw std::underflow_error("Subtraction result would be negative.");
    }

    int carry = 0;
    for (size_t i = 0; i < _size; i++) {
        int otherDigit = (i < other._size) ? (other._data[other._size - i - 1] - '0') : 0;
        int diff = (_data[_size - i - 1] - '0') - otherDigit - carry;

        if (diff < 0) {
            _data[_size - i - 1] = diff + 2 + '0';
            carry = 1;
        } else {
            _data[_size - i - 1] = diff + '0';
            carry = 0;
        }
    }

    if (carry != 0) {
        throw std::underflow_error("Subtraction result would be negative.");
    }

    return *this;
}

unsigned char *Binary::getData() {
    return _data;
}

size_t Binary::getSize() const {
    return _size;
}