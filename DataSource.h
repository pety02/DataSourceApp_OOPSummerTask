#ifndef DATASOURCE_H
#define DATASOURCE_H

#include "Vector.h"

template <typename T>
class DataSource {
private:
public:
    virtual T& get() = 0;
    virtual Vector<T> getSequence(int) = 0; 
    virtual bool hasNext() const = 0;
    virtual bool reset() = 0; 
    virtual T& operator()() = 0;
    explicit operator bool() const {
        return this->hasNext();
    }
};

#include "DataSource.inl"

#endif