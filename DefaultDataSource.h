#pragma once
#ifndef DEFAULTDATASOURCE_H
#define DEFAULTDATASOURCE_H

#include "DataSource.h"

template <typename T>
class DefaultDataSource final : public DataSource<T> {
public:
    DefaultDataSource();
    T& get() override;
    Vector<T> getSequence(int) override;
};

#include "DefaultDataSource.inl"

#endif
