#pragma once
#ifndef ALTERNATEDATASOURCE_H
#define ALTERNATEDATASOURCE_H

#include "DataSource.h"

template <typename T>
class AlternateDataSource final : public DataSource<T> {
private:
    DataSource<T>** sources;
    int sourcesCount;
    AlternateDataSource();

    void copy(const AlternateDataSource&);
    void destroy();
public:
    AlternateDataSource(const AlternateDataSource&);
    AlternateDataSource(AlternateDataSource&&) noexcept;
    AlternateDataSource& operator=(const AlternateDataSource&);
    AlternateDataSource& operator=(AlternateDataSource&&) noexcept;
    AlternateDataSource(DataSource<T>*[], int); 
    ~AlternateDataSource();

    bool hasNext() const override;
    Vector<T> getSequence(int) override;
};

#include "AlternateDataSource.inl"

#endif