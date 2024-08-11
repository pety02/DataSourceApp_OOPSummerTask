#pragma once
#ifndef ALTERNATEDATASOURCE_INL
#define ALTERNATEDATASOURCE_INL

#include "AlternateDataSource.h"

template <typename T>
inline void AlternateDataSource<T>::copy(const AlternateDataSource<T>& other)
{
    this->data = other.data;
    this->currDataIndex = other.currDataIndex;
    this->sourcesCount = other.sourcesCount;
    this->sources = new DataSource<T>*[this->sourcesCount];
    for(int i = 0; i < this->sourcesCount; ++i) {
        this->sources[i] = other.sources[i];
    }
}

template <typename T>
inline void AlternateDataSource<T>::destroy()
{
    for(int i = 0; i < this->sourcesCount; ++i) {
        delete this->sources[i];
    }

    delete[] this->sources;
}

template <typename T>
inline AlternateDataSource<T>::AlternateDataSource(DataSource<T>** sources, int sourcesCount)
{
    this->currDataIndex = 0;
    this->sourcesCount = sourcesCount;
    this->sources = new DataSource<T>*[this->sourcesCount];
    for (int i = 0; i < sourcesCount; ++i) {
        this->sources[i] = sources[i];
    }
}

template <typename T>
inline AlternateDataSource<T>::AlternateDataSource(const AlternateDataSource<T>& other)
{
    this->copy(other);
}

template <typename T>
inline AlternateDataSource<T>::AlternateDataSource(AlternateDataSource<T>&& other) noexcept
{
    this->copy(other);
    this->sources = nullptr;
}

template <typename T>
inline AlternateDataSource<T>& AlternateDataSource<T>::operator=(const AlternateDataSource<T>& other)
{
    if(this != &other) {
        this->destroy();
        this->copy(other);
    }

    return *this;
}

template <typename T>
inline AlternateDataSource<T>& AlternateDataSource<T>::operator=(AlternateDataSource<T>&& other) noexcept
{
    if(this != &other) {
        this->destroy();
        this->copy(other);
        other.sources = nullptr;
    }

    return *this;
}

template <typename T>
inline T AlternateDataSource<T>::get()
{
    int sourceIndex = this->currDataIndex % this->sourcesCount;
    try {
        T el = this->sources[sourceIndex]->get();
        this->currDataIndex++;
        return el;
    } catch (std::exception&) {
        sourceIndex = (++this->currDataIndex) % this->sourcesCount;
        return this->sources[sourceIndex]->get();
    }
}

template <typename T>
inline Vector<T> AlternateDataSource<T>::getSequence(int count)
{
    Vector<T> sequence = Vector<T>();
    for(int i = 0; i < count; ++i) {
        T value = this->get();
        sequence.append(value);
    }

    return sequence;
}

template <typename T>
inline bool AlternateDataSource<T>::hasNext() const
{   
    for(int i = 0; i < this->sourcesCount; ++i) {
        DataSource<T>* currentSource = this->sources[i];
        if(currentSource->hasNext()) {
            return true;
        }
    }
    
    return false;
}

template <typename T>
inline bool AlternateDataSource<T>::reset()
{
    return true;
}

template <typename T>
inline T AlternateDataSource<T>::operator()()
{
    return this->get();
}

template <typename T>
inline AlternateDataSource<T>::~AlternateDataSource()
{
    this->destroy();
}

#endif