#pragma once
#ifndef DEFAULTDATASOURCE_INL
#define DEFAULTDATASOURCE_INL

#include "DefaultDataSource.h"

template <typename T>
inline DefaultDataSource<T>::DefaultDataSource() {
    this->data = Vector<T>();
    this->currDataIndex = 0;
}

template <typename T>
inline T& DefaultDataSource<T>::get() {
    if (this->hasNext()) {
        return this->data[++this->currDataIndex];
    }

    T* current = new T();
    return *current;
}

template <typename T>
inline Vector<T> DefaultDataSource<T>::getSequence(int count) {
    if (count < this->data.size()) {
        return this->data;
    }

    Vector<T> current = this->data;
    int sizeSustraction = count - this->data.size();
    for (int i = 0; i < sizeSustraction; ++i) {
        current.append(T());
        this->currDataIndex++;
    }

    return current;
}

#endif
