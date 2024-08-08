#pragma once
#ifndef DATASOURCE_INL
#define DATASOURCE_INL

#include "DataSource.h"

template <typename T>
inline DataSource<T>::DataSource()
{
    this->data = Vector<T>();
    this->currDataIndex = 0;
}

template <typename T>
inline T& DataSource<T>::get()
{
    if (this->hasNext()) {
        return this->data[++this->currDataIndex];
    }

    throw std::out_of_range("Index out of bound!");
}

template <typename T>
inline bool DataSource<T>::hasNext() const
{
    return this->currDataIndex < this->data.size();
}

template <typename T>
inline void DataSource<T>::reset()
{
    this->currDataIndex = 0;
}

template <typename T>
inline T& DataSource<T>::operator()() const
{
    return this->get();
}

template <typename T>
inline DataSource<T>::operator bool()
{
    return this->hasNext();
}

template <typename T>
inline DataSource<T>::~DataSource()
{
    this->data.~Vector();
    this->currDataIndex = 0;
}

template <typename T>
inline Vector<T> DataSource<T>::getData()
{
    return this->data;
}

#endif
