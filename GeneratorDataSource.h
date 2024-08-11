#pragma once
#ifndef GENERATORDATASOURCE_H
#define GENERATORDATASOURCE_H

#include "DataSource.h"

template <typename T>
class GeneratorDataSource final : public DataSource<T>
{
private:
	Vector<T>(*fnc)(int);
    Vector<T> miniedData;
	int lastGeneratedElIndex;
public:
	GeneratorDataSource(Vector<T>(*)(int));
	T& get() override;
    Vector<T> getSequence(int) override; 
    bool hasNext() const override;
    bool reset() override; 
    T& operator()() override;
};

#include "GeneratorDataSource.inl"

#endif