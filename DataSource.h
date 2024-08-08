#ifndef DATASOURCE_H
#define DATASOURCE_H

#include "Vector.h"
#include <fstream>
#include <cmath>

template <typename T>
class DataSource {
protected:
    Vector<T> data;
    int currDataIndex;

public:
    DataSource();
    virtual T& get();
    virtual Vector<T> getSequence(int) = 0;
    bool hasNext() const;
    void reset();
    T& operator()() const;
    //friend std::istream& operator>>(std::istream&, DataSource*);  // TODO: to think it
    operator bool();
    virtual ~DataSource();
    Vector<T> getData();
};

#include "DataSource.inl"

#endif
