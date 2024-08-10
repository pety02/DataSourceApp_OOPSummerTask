#pragma once
#ifndef DEFAULTDATASOURCE_INL
#define DEFAULTDATASOURCE_INL

#include "DefaultDataSource.h"

template <typename T>
inline DefaultDataSource<T>::DefaultDataSource() {
    this->data = Vector<T>();
    this->miniedData = Vector<T>();
    this->currDataIndex = 0;
}

template <typename T>
inline T& DefaultDataSource<T>::get() {
    this->miniedData.append(T());
    return this->miniedData[this->currDataIndex++];
}

template <typename T>
inline Vector<T> DefaultDataSource<T>::getSequence(int count) {
    for (int i = 0; i < count; ++i) {
        this->miniedData.append(T());
        this->currDataIndex++;
    }

    return this->miniedData;
}

template <typename T>
inline bool DefaultDataSource<T>::hasNext() const
{
    return true;
}

#endif