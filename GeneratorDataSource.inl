#pragma once
#ifndef GENERATORDATASOURCE_INL
#define GENERATORDATASOURCE_INL

#include "GeneratorDataSource.h"

template<typename T>
inline GeneratorDataSource<T>::GeneratorDataSource()
{
	this->data = Vector<T>();
	this->currDataIndex = 0;
	this->fnc = nullptr;
}

template<typename T>
inline Vector<T> GeneratorDataSource<T>::getSequence(int count)
{
	//int minCount = std::min(this->data.size(), count);
	for (int i = 1; i < count; ++i) {
		this->get();
	}
	return this->data;
}

template<typename T>
inline T& GeneratorDataSource<T>::get()
{
	T* currData = new T();
	*currData = this->fnc((T)(this->currDataIndex++));
	this->data.append(*currData);
	return *currData;
}

template<typename T>
inline GeneratorDataSource<T>::GeneratorDataSource(T(*generatorFunc)(T num))
{
	this->fnc = generatorFunc;
	this->data = Vector<T>();
	this->currDataIndex = 0;
	this->data.append(generatorFunc((T)(this->currDataIndex++)));
}

#endif
