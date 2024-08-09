#pragma once
#ifndef GENERATORDATASOURCE_INL
#define GENERATORDATASOURCE_INL

#include "GeneratorDataSource.h"

template<typename T>
inline GeneratorDataSource<T>::GeneratorDataSource()
{
	this->data = Vector<T>();
	this->currDataIndex = 0;
	Vector<T>(*this->fnc)();
	this->lastGeneratedEl = 0;
}

template<typename T>
inline Vector<T> GeneratorDataSource<T>::getSequence(int count)
{
	Vector<T> v = this->fnc(count);
	this->lastGeneratedEl = v.size();
	return v;
}

template<typename T>
inline T& GeneratorDataSource<T>::get()
{
	this->data = this->getSequence(this->lastGeneratedEl + 1);
	T& toBeReturned = this->data[this->lastGeneratedEl - 1];
	return toBeReturned;
}

template<typename T>
inline GeneratorDataSource<T>::GeneratorDataSource(Vector<T>(*generatorFunc)(int count))
{
	this->fnc = generatorFunc;
	this->currDataIndex = 0;
	this->data = generatorFunc(0);
	this->lastGeneratedEl = 0;
}

#endif
