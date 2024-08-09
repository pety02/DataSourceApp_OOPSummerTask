#pragma once
#ifndef ARRAYDATASOURCE_H
#define ARRAYDATASOURCE_H

#include "DataSource.h"

template <typename T>
class ArrayDataSource final : public DataSource<T> {
private:
    ArrayDataSource();
public:
    ArrayDataSource(T*, int);
    Vector<T> getSequence(int) override;
    const ArrayDataSource& operator+(const T&) const;
    ArrayDataSource& operator+=(T);
    ArrayDataSource& operator--();
    ArrayDataSource& operator--(int);
};

#include "ArrayDataSource.inl"

#endif

