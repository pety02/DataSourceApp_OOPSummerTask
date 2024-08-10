#pragma once
#ifndef GENERATORDATASOURCE_H
#define GENERATORDATASOURCE_H

#include "DataSource.h"

template <typename T>
class GeneratorDataSource final : public DataSource<T>
{
private:
	Vector<T>(*fnc)(int);
	int lastGeneratedEl;
	
	GeneratorDataSource();
public:
	GeneratorDataSource(Vector<T>(*)(int));
	Vector<T> getSequence(int) override;
	T& get() override;
	bool hasNext() const override;
	bool reset() override;
};

#include "GeneratorDataSource.inl"

#endif

