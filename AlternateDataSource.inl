#pragma once
#ifndef ALTERNATEDATASOURCE_INL
#define ALTERNATEDATASOURCE_INL

#include "AlternateDataSource.h"

template <typename T>
inline AlternateDataSource<T>::AlternateDataSource()
{
    this->data = Vector<DataSource<T>*>();
    this->currDataIndex = 0;
    this->sources = nullptr;
}

template <typename T>
inline AlternateDataSource<T>::AlternateDataSource(DataSource<T>* sources[], int size)
{
    this->data = Vector<T>();
    this->currDataIndex = 0;
    this->sources = new DataSource<T>*[size];
    for (int i = 0; i < size; ++i) {
        this->sources[i] = sources[i];
    }

    int minElementsCount = INT_MAX;
    for (int i = 0; i < size; ++i) {
        DataSource<T>* currSourcePtr = sources[i];
        if (currSourcePtr->getData().size() < minElementsCount 
            && dynamic_cast<GeneratorDataSource<T>*>(currSourcePtr) == nullptr) {
            minElementsCount = currSourcePtr->getData().size();
        }
    }

    for (int i = 0; i < minElementsCount; ++i) {
        for (int j = 0; j < size; ++j) {
            DataSource<T>* currSourcePtr = sources[j];
            if (dynamic_cast<GeneratorDataSource<T>*>(currSourcePtr) == nullptr) {
                this->data.append(currSourcePtr->getData()[i]);
                this->currDataIndex++;
            }
            else {
                this->data.append(currSourcePtr->get());
                this->currDataIndex++;
            }
        }
    }
}

template <typename T>
inline Vector<T> AlternateDataSource<T>::getSequence(int count)
{
    Vector<T> current = Vector<T>();
    int minCount = std::min(this->data.size(), count);
    for (int i = 0; i < minCount; ++i) {
        current.append(this->data[i]);
    }
    
    for (int i = this->currDataIndex; i < count;) {
        for(int j = 0; j < 3; ++j) {
            if(i == count) {
                break;
            }
            DataSource<T>* currSourcePtr = this->sources[j];
            if (dynamic_cast<GeneratorDataSource<T>*>(currSourcePtr) != nullptr) {
                current.append(currSourcePtr->get());
                i++;
                this->currDataIndex++;
            }
        }
    }
    return current;
}

#endif