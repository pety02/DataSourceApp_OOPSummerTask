#pragma once
#ifndef DATASOURCE_INL
#define DATASOURCE_INL

#include "DataSource.h"

template <typename T>
inline Vector<T> DataSource<T>::getAllData() const
{
    return this->data;
}

template <typename T>
inline DataSource<T>::DataSource()
{
    this->data = Vector<T>();
    this->miniedData = Vector<T>();
    this->currDataIndex = 0;
}

template <typename T>
inline T& DataSource<T>::get()
{
    if (!this->hasNext()) {
        throw std::out_of_range("Index out of bound!");
    }

    this->miniedData.append(this->data[this->currDataIndex]);
    return this->miniedData[this->currDataIndex++];
}

template <typename T>
inline bool DataSource<T>::hasNext() const
{
    return this->currDataIndex < this->data.size();
}

template <typename T>
inline bool DataSource<T>::reset()
{
    this->currDataIndex = 0;
    this->miniedData = Vector<T>();
    return true;
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
inline Vector<T> DataSource<T>::getData() const
{
    return this->miniedData;
}

#endif