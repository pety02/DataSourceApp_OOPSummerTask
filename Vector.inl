#pragma once
#ifndef VECTOR_INL
#define VECTOR_INL

#include "Vector.h"

template <typename T>
inline void Vector<T>::copy(const Vector<T>& other)
{
    this->capacity = other.capacity;
    this->index = other.index;
    this->data = new T[other.capacity];
    for (int i = 0; i < other.index; ++i) {  
        this->data[i] = other.data[i];
    }
}

template <typename T>
inline void Vector<T>::destroy()
{
    delete[] this->data;
}

template <typename T>
inline void Vector<T>::resize()
{
    this->capacity *= 2;
    T* temp = new T[this->capacity];
    for (int i = 0; i < this->index; ++i) {
        temp[i] = this->data[i];
    }

    this->destroy();
    this->data = temp;
}

template <typename T>
inline Vector<T>::Vector()
{
    this->capacity = 8;
    this->index = 0;
    this->data = new T[this->capacity];
}

template <typename T>
inline Vector<T>::Vector(const Vector<T>& other)
{
    this->copy(other);
}

template <typename T>
inline Vector<T>::Vector(Vector<T>&& other) noexcept
{
    this->copy(other);
    other.data = nullptr;
}

template <typename T>
inline Vector<T>& Vector<T>::operator=(const Vector<T>& other)
{
    if (this != &other) {
        this->destroy();
        this->copy(other);
    }

    return *this;
}

template <typename T>
inline Vector<T>& Vector<T>::operator=(Vector<T>&& other) noexcept
{
    if (this != &other) {
        this->destroy();
        this->copy(other);

        other.data = nullptr;
    }

    return *this;
}

template <typename T>
inline Vector<T>::~Vector()
{
    this->destroy();
}

template <typename T>
inline T& Vector<T>::operator[](int index)
{
    if (index < 0 || this->index <= index) {
        throw std::out_of_range("Index out of bound!");
    }

    return this->data[index];
}

template <typename T>
inline const T Vector<T>::operator[](int index) const
{
    if (index < 0 || this->index <= index) {
        throw std::out_of_range("Index out of bound!");
    }

    return this->data[index];
}

template <typename T>
inline void Vector<T>::append(const T& el)
{
    if (this->index == this->capacity) {
        this->resize();
    }
    this->data[this->index++] = el;
}

template <typename T>
inline void Vector<T>::remove(int index)
{
    if (this->index <= index) {
        return;
    }

    for (int i = index; i < this->index - 1; ++i) {
        this->data[i] = this->data[i + 1];
    }
    this->index--;
}

template <typename T>
inline int Vector<T>::size() const
{
    return this->index;
}

template <typename T>
inline void Vector<T>::print() const
{
    for (int i = 0; i < this->index; ++i) {
        if (i == this->index - 1) {
            std::cout << this->data[i] << std::endl;
            break;
        }
        std::cout << this->data[i] << " ";
    }
}

template<typename T>
inline T* Vector<T>::getData() const
{
    return this->data;
}

#endif