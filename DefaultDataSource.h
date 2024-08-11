#pragma once
#ifndef DEFAULTDATASOURCE_H
#define DEFAULTDATASOURCE_H

#include "DataSource.h"

template <typename T>
class DefaultDataSource final : public DataSource<T> {
private:
public:
    DefaultDataSource();
    T get() override;
    Vector<T> getSequence(int) override; 
    bool hasNext() const override;
    bool reset() override; 
    T operator()() override;
};

#include "DefaultDataSource.inl"

#endif
