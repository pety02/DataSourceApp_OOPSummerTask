#ifndef DATASOURCE_H
#define DATASOURCE_H

#include "Vector.h"
#include <fstream>
#include <cmath>

template <typename T>
class DataSource {
protected:
    Vector<T> data;
    Vector<T> miniedData;
    int currDataIndex;

public:
    DataSource();
    virtual T& get();
    virtual Vector<T> getSequence(int) = 0; 
    virtual bool hasNext() const;
    virtual bool reset(); 
    T& operator()() const;
    operator bool(); 
    virtual ~DataSource();
    Vector<T> getAllData() const;
    Vector<T> getData() const ;
    template <typename U>
    friend DataSource<T>& operator>>(DataSource<T>& src, U value) {
        for(int i = 0; i < src.getAllData().size(); ++i) {
            if(src.getAllData()[i] == value) {
                src.miniedData.append(value);
                src.currDataIndex++;
                break;
            }
        }
        return src;
    }
};

#include "DataSource.inl"

#endif