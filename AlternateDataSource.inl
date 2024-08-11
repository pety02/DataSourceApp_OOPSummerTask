#pragma once
#ifndef ALTERNATEDATASOURCE_INL
#define ALTERNATEDATASOURCE_INL

#include "AlternateDataSource.h"

template <typename T>
inline AlternateDataSource<T>::AlternateDataSource(DataSource<T>* sources[], int sourcesCount)
{
    this->data = Vector<T>();
    this->currDataIndex = 0;
    this->sources = Vector<DataSource<T>*>();
    for (int i = 0; i < sourcesCount; ++i) {
        this->sources.append(sources[i]);
    }
}

template <typename T>
inline T& AlternateDataSource<T>::get()
{
    int sourceIndex = this->currDataIndex % this->sources.size();
    try {
        T& el = this->sources[sourceIndex]->get();
        this->currDataIndex++;
        return el;
    } catch (std::exception&) {
        sourceIndex = (++this->currDataIndex) % this->sources.size();
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
    for(int i = 0; i < this->sources.size(); ++i) {
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
inline T& AlternateDataSource<T>::operator()()
{
    return this->get();
}

#endif