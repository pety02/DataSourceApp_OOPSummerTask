#pragma once
#ifndef ARRAYDATASOURCE_INL
#define ARRAYDATASOURCE_INL

#include "ArrayDataSource.h"

template <typename T>
inline ArrayDataSource<T>::ArrayDataSource()
{
    this->data = Vector<T>();
    this->miniedData = Vector<T>();
    this->currDataIndex = 0;
}

template <typename T>
inline ArrayDataSource<T>::ArrayDataSource(T* data, int size)
{
    this->data = Vector<T>();
    this->miniedData = Vector<T>();
    this->currDataIndex = 0;
    for (int i = 0; i < size; ++i) {
        this->data.append(data[i]);
    }
}

template <typename T>
inline Vector<T> ArrayDataSource<T>::getSequence(int count)
{
    int minCount = std::min(this->data.size(), count);
    for (int i = 0; i < minCount; ++i) {
        try {
            T el = this->data[i];
            this->miniedData.append(el);
            this->currDataIndex++;
        } catch (std::out_of_range& ex) {
            break;
        }
    }
    return this->miniedData;
}

template <typename T>
inline const ArrayDataSource<T>& ArrayDataSource<T>::operator+(const T& el) const
{
    ArrayDataSource<T>* result = new ArrayDataSource<T>(*this);  
    *result += el;                     
    return *result; 
}

template <typename T>
inline ArrayDataSource<T>& ArrayDataSource<T>::operator+=(T el)
{
    this->data.append(el);
    return *this;
}

template <typename T>
inline ArrayDataSource<T>& ArrayDataSource<T>::operator--()
{
    if(0 < this->miniedData.size()) {
        this->currDataIndex--;
        this->miniedData.remove(0);
    }

    return *this;
}

template <typename T>
inline ArrayDataSource<T>& ArrayDataSource<T>::operator--(int)
{
    if(0 < this->miniedData.size()) {
        this->currDataIndex--;
        this->miniedData.remove(0);
    }

    return *this;
}

#endif
