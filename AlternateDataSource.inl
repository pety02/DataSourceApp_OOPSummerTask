#pragma once
#ifndef ALTERNATEDATASOURCE_INL
#define ALTERNATEDATASOURCE_INL

#include "AlternateDataSource.h"
#include "GeneratorDataSource.h"

template <typename T>
inline AlternateDataSource<T>::AlternateDataSource()
{
    this->data = Vector<T>();
    this->miniedData = Vector<T>();
    this->currDataIndex = 0;
    this->sourcesCount = 0;
    this->sources = nullptr;
}

template <typename T>
inline void AlternateDataSource<T>::copy(const AlternateDataSource<T>& other)
{
    this->data = other.data;
    this->miniedData = other.miniedData;
    this->currDataIndex = other.currDataIndex;
    this->sourcesCount = other.sourcesCount;
    for(int i = 0; i < this->sourcesCount; ++i) {
        this->sources[i] = other.sources[i];
    }
}

template <typename T>
inline void AlternateDataSource<T>::destroy()
{
    delete[] this->sources;
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
    other.data = Vector<T>();
    other.miniedData = Vector<T>();
    other.currDataIndex = 0;
    other.sourcesCount = 0;
    other.sources = nullptr;
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
        other.data = Vector<T>();
        other.miniedData = Vector<T>();
        other.currDataIndex = 0;
        other.sourcesCount = 0;
        other.sources = nullptr;
    }

    return *this;
}

template <typename T>
inline AlternateDataSource<T>::AlternateDataSource(DataSource<T>* sources[], int sourcesCount)
{
    this->data = Vector<T>();
    this->miniedData = Vector<T>();
    this->currDataIndex = 0;
    this->sourcesCount = sourcesCount;
    this->sources = new DataSource<T>*[sourcesCount];
    for (int i = 0; i < sourcesCount; ++i) {
        this->sources[i] = sources[i];
    }

    int minElementsCount = INT_MAX;
    for (int i = 0; i < sourcesCount; ++i) {
        DataSource<T>* currSourcePtr = sources[i];
        if (currSourcePtr->getData().size() < minElementsCount 
            && dynamic_cast<GeneratorDataSource<T>*>(currSourcePtr) == nullptr) {
            minElementsCount = currSourcePtr->getAllData().size();
        }
    }

    for (int i = 0; i < minElementsCount; ++i) {
        for (int j = 0; j < sourcesCount; ++j) {
            DataSource<T>* currSourcePtr = sources[j];
            if (dynamic_cast<GeneratorDataSource<T>*>(currSourcePtr) == nullptr) {
                this->data.append(currSourcePtr->getAllData()[i]);
            }
            else {
                this->data.append(currSourcePtr->get());
            }
        }
    }
}

template <typename T>
inline AlternateDataSource<T>::~AlternateDataSource()
{
    this->destroy();
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
inline Vector<T> AlternateDataSource<T>::getSequence(int count)
{
    int minCount = std::min(this->data.size(), count);
    for (int i = 0; i < minCount; ++i) {
        this->miniedData.append(this->data[i]);
        this->currDataIndex++;
    }
    
    for (int i = this->currDataIndex; i < count;) {
        for(int j = 0; j < this->sourcesCount; ++j) {
            if(i == count) {
                break;
            }
            DataSource<T>* currSourcePtr = this->sources[j];
            if (dynamic_cast<GeneratorDataSource<T>*>(currSourcePtr) != nullptr) {
                try {
                    T el = currSourcePtr->get();
                    this->miniedData.append(el);
                    i++;
                    this->currDataIndex++;
                } catch (std::out_of_range& ex) {
                    break;
                } 
            }
        }
    }
    return this->miniedData;
}

#endif