#pragma once
#ifndef GENERATORDATASOURCE_H
#define GENERATORDATASOURCE_H

#include "DataSource.h"

template <typename T>
class GeneratorDataSource final : public DataSource<T>
{
private:
	GeneratorDataSource();
	T(*fnc)(T);
public:
	GeneratorDataSource(T(*)(T));
	Vector<T> getSequence(int) override;
	T& get() override;
};

#include "GeneratorDataSource.inl"

#endif

