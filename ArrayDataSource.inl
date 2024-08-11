#pragma once
#ifndef ARRAYDATASOURCE_INL
#define ARRAYDATASOURCE_INL

#include "ArrayDataSource.h"

template <typename T>
inline ArrayDataSource<T>::ArrayDataSource(T* data, int size)
{
    this->currDataIndex = 0;
    for (int i = 0; i < size; ++i) {
        this->data.append(data[i]);
    }
}

template <typename T>
inline T ArrayDataSource<T>::get()
{
    if(this->data.size() <= this->currDataIndex) {
        throw std::out_of_range("Index out of bound!");
    }

    return this->data[this->currDataIndex++];
}

template <typename T>
inline Vector<T> ArrayDataSource<T>::getSequence(int count)
{
    Vector<T> sequnece = Vector<T>();
    int minCount = std::min(this->data.size(), count);
    for (int i = 0; i < minCount; ++i) {
        try {
            T el = this->data[i];
            sequnece.append(el);
            this->currDataIndex++;
        } catch (std::out_of_range&) {
            break;
        }
    }
    return sequnece;
}

template <typename T>
inline bool ArrayDataSource<T>::hasNext() const
{
    return this->currDataIndex < this->data.size();
}

template <typename T>
inline bool ArrayDataSource<T>::reset()
{
    return true;
}

template <typename T>
inline T ArrayDataSource<T>::operator()()
{
    return this->get();
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
    this->currDataIndex--;
    return *this;
}

template <typename T>
inline ArrayDataSource<T>& ArrayDataSource<T>::operator--(int)
{
    this->currDataIndex--;
    return *this;
}

#endif