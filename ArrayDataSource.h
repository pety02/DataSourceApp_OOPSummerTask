#pragma once
#ifndef ARRAYDATASOURCE_H
#define ARRAYDATASOURCE_H

#include "DataSource.h"

template <typename T>
class ArrayDataSource final : public DataSource<T> {
private:
    Vector<T> data;
    int currDataIndex;
public:
    ArrayDataSource(T*, int);
    T& get() override;
    Vector<T> getSequence(int) override; 
    bool hasNext() const override;
    bool reset() override; 
    T& operator()() override;
    const ArrayDataSource& operator+(const T&) const;
    ArrayDataSource& operator+=(T);
    ArrayDataSource& operator--();
    ArrayDataSource& operator--(int);
};

#include "ArrayDataSource.inl"

#endif

