#pragma once
#ifndef VECTOR_H
#define VECTOR_H

#include <stdexcept>
#include <iostream>

template <typename T>
class Vector final {
private:
    T* data;
    int capacity;
    int index;

    void copy(const Vector&);
    void destroy();
    void resize();

public:
    Vector();
    Vector(const Vector&);
    Vector(Vector&&) noexcept;
    Vector& operator=(const Vector&);
    Vector& operator=(Vector&&) noexcept;
    ~Vector();

    T& operator[](int);
    const T operator[](int) const;

    void append(const T&);
    void remove(int);

    int size() const;
    void print() const;
    T* getData() const;
};

#include "Vector.inl"

#endif

