#pragma once
#ifndef ALTERNATEDATASOURCE_H
#define ALTERNATEDATASOURCE_H

#include "GeneratorDataSource.h"

template <typename T>
class AlternateDataSource final : public DataSource<T> {
private:
    DataSource<T>** sources;
    AlternateDataSource();
public:
    AlternateDataSource(DataSource<T>* [], int);
    Vector<T> getSequence(int) override;
};

#include "AlternateDataSource.inl"

#endif

