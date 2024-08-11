#pragma once
#ifndef DEFAULTDATASOURCE_INL
#define DEFAULTDATASOURCE_INL

#include "DefaultDataSource.h"

template <typename T>
inline DefaultDataSource<T>::DefaultDataSource() {
}

template <typename T>
inline T DefaultDataSource<T>::get() {
    Vector<T> sequence = Vector<T>(this->getSequence(1));
    T el = sequence[0];
    return el;
}

template <typename T>
inline Vector<T> DefaultDataSource<T>::getSequence(int count) {
    Vector<T> sequence = Vector<T>();
    for (int i = 0; i < count; ++i) {
        sequence.append(T());
    }

    return sequence;
}

template <typename T>
inline bool DefaultDataSource<T>::hasNext() const
{
    return true;
}

template <typename T>
inline bool DefaultDataSource<T>::reset()
{
    return true;
}

template <typename T>
inline T DefaultDataSource<T>::operator()()
{
    return this->get();
}

#endif