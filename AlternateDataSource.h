#pragma once
#ifndef ALTERNATEDATASOURCE_H
#define ALTERNATEDATASOURCE_H

#include "DataSource.h"

template <typename T>
class AlternateDataSource final : public DataSource<T> {
private:
    Vector<T> data;
    int currDataIndex;
    Vector<DataSource<T>*> sources;
public:
    AlternateDataSource(DataSource<T>*[], int); 
    T& get() override;
    Vector<T> getSequence(int) override; 
    bool hasNext() const override;
    bool reset() override; 
    T& operator()() override;
};

#include "AlternateDataSource.inl"

#endif