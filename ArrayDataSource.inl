#pragma once
#ifndef ARRAYDATASOURCE_INL
#define ARRAYDATASOURCE_INL

#include "ArrayDataSource.h"

template <typename T>
inline ArrayDataSource<T>::ArrayDataSource()
{
    this->data = Vector<T>();
    this->currDataIndex = 0;
}

template <typename T>
inline ArrayDataSource<T>::ArrayDataSource(T* data, int size)
{
    this->data = Vector<T>();
    this->currDataIndex = 0;
    for (int i = 0; i < size; ++i) {
        this->data.append(data[i]);
    }
}

template <typename T>
inline Vector<T> ArrayDataSource<T>::getSequence(int count)
{
    Vector<T> current = Vector<T>();
    int minCount = std::min(this->data.size(), count);
    for (int i = 0; i < minCount; ++i) {
        current.append(this->data[i]);
        this->currDataIndex++;
    }
    return current;
}

template <typename T>
inline const ArrayDataSource<T>& ArrayDataSource<T>::operator+(const T& el) const
{
    ArrayDataSource<T>* src = this;
    src->data.append(el);

    return *src;
}

template <typename T>
inline ArrayDataSource<T>& ArrayDataSource<T>::operator+=(const T& el)
{
    this->data.append(el);
    return *this;
}

template <typename T>
inline ArrayDataSource<T>& ArrayDataSource<T>::operator-()
{
    this->currDataIndex--;
    return *this;
}

template <typename T>
inline ArrayDataSource<T>& ArrayDataSource<T>::operator-(int)
{
    this->currDataIndex--;
    return *this;
}

#endif
