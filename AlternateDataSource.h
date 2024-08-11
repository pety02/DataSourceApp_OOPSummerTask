#pragma once
#ifndef ALTERNATEDATASOURCE_H
#define ALTERNATEDATASOURCE_H

#include "DataSource.h"

template <typename T>
class AlternateDataSource final : public DataSource<T> {
private:
    Vector<T> data;
    int currDataIndex;
    DataSource<T>** sources;
    int sourcesCount; 

    void copy(const AlternateDataSource&);
    void destroy();
public:
    AlternateDataSource(DataSource<T>**, int); 
    AlternateDataSource(const AlternateDataSource&);
    AlternateDataSource(AlternateDataSource&&) noexcept;
    AlternateDataSource& operator=(const AlternateDataSource&);
    AlternateDataSource& operator=(AlternateDataSource&&) noexcept;
    T get() override;
    Vector<T> getSequence(int) override; 
    bool hasNext() const override;
    bool reset() override; 
    T operator()() override;
    ~AlternateDataSource();
};

#include "AlternateDataSource.inl"

#endif