#pragma once
#ifndef GENERATORDATASOURCE_INL
#define GENERATORDATASOURCE_INL

#include "GeneratorDataSource.h"

template<typename T>
inline GeneratorDataSource<T>::GeneratorDataSource(Vector<T>(*generatorFunc)(int count))
{
	this->fnc = generatorFunc;
	this->miniedData = Vector<T>();
	this->lastGeneratedElIndex = 0;
}

template<typename T>
inline T& GeneratorDataSource<T>::get()
{
	this->miniedData = this->getSequence(this->lastGeneratedElIndex + 1);
	T& toBeReturned = this->miniedData[this->lastGeneratedElIndex - 1];
	return toBeReturned;
}

template <typename T>
inline Vector<T> GeneratorDataSource<T>::getSequence(int count)
{
	this->miniedData = this->fnc(count);
	this->lastGeneratedElIndex = this->miniedData.size();
	return miniedData;
}

template <typename T>
inline bool GeneratorDataSource<T>::hasNext() const
{
    return true;
}

template <typename T>
inline bool GeneratorDataSource<T>::reset()
{
	this->lastGeneratedElIndex = 0;
	int miniedDataSize = this->miniedData.size();
	Vector<T> newlyGeneratedData = this->fnc(miniedDataSize);
	for(int i = 0; i < miniedDataSize; ++i) {
		if(this->miniedData[i] != newlyGeneratedData[i]) {
			return false;
		}
	}

	this->miniedData = Vector<T>();
	this->lastGeneratedElIndex = 0;
    return true;
}

template <typename T>
inline T &GeneratorDataSource<T>::operator()()
{
    return this->get();
}

#endif