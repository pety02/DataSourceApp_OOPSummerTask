#pragma once
#ifndef GENERATORDATASOURCE_INL
#define GENERATORDATASOURCE_INL

#include "GeneratorDataSource.h"

template<typename T>
inline GeneratorDataSource<T>::GeneratorDataSource()
{
	this->data = Vector<T>();
	this->miniedData = Vector<T>();
	this->currDataIndex = 0;
	Vector<T>(*this->fnc)();
	this->lastGeneratedEl = 0;
}

template <typename T>
inline Vector<T> GeneratorDataSource<T>::getSequence(int count)
{
	this->miniedData = this->fnc(count);
	this->lastGeneratedEl = this->miniedData.size();
	this->currDataIndex += this->miniedData.size();
	return this->miniedData;
}

template<typename T>
inline T& GeneratorDataSource<T>::get()
{
	this->miniedData = this->getSequence(this->lastGeneratedEl + 1);
	T& toBeReturned = this->miniedData[this->lastGeneratedEl - 1];
	this->currDataIndex++;
	return toBeReturned;
}

template <typename T>
inline bool GeneratorDataSource<T>::hasNext() const
{
    return true;
}

template <typename T>
inline bool GeneratorDataSource<T>::reset()
{
	this->lastGeneratedEl = 0;
	this->currDataIndex = 0;
	int miniedDataSize = this->miniedData.size();
	Vector<T> newlyGeneratedData = this->fnc(miniedDataSize);
	for(int i = 0; i < miniedDataSize; ++i) {
		if(this->miniedData[i] != newlyGeneratedData[i]) {
			return false;
		}
	}

	this->miniedData = Vector<T>();
	this->lastGeneratedEl = 0;
	this->currDataIndex = 0;
    return true;
}

template<typename T>
inline GeneratorDataSource<T>::GeneratorDataSource(Vector<T>(*generatorFunc)(int count))
{
	this->fnc = generatorFunc;
	this->currDataIndex = 0;
	this->data = generatorFunc(0);
	this->miniedData = Vector<T>();
	this->lastGeneratedEl = 0;
}

#endif