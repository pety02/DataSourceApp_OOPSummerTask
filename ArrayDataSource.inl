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
    ArrayDataSource<T>* result = new ArrayDataSource<T>(*this);  
    *result += el;   
    result->currDataIndex++;                   
    return *result; 
}

template <typename T>
inline ArrayDataSource<T>& ArrayDataSource<T>::operator+=(T el)
{
    this->data.append(el);
    this->currDataIndex++;
    return *this;
}

template <typename T>
inline ArrayDataSource<T>& ArrayDataSource<T>::operator--()
{
    if(0 < this->data.size()) {
        this->currDataIndex;
        this->data.remove(0);
    }

    return *this;
}

template <typename T>
inline ArrayDataSource<T>& ArrayDataSource<T>::operator--(int)
{
    if(0 < this->data.size()) {
        this->currDataIndex;
        this->data.remove(0);
    }

    return *this;
}

#endif
