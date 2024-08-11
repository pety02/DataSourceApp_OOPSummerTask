#pragma once
#ifndef FILEDATASOURCE_H
#define FILEDATASOURCE_H

#include <fstream>
#include <cstring>
#include <cstdlib>   
#include <cassert>  
#include "DataSource.h"

template <typename T>
class FileDataSource final : public DataSource<T> {
private:
    char* filename;
    Vector<T> data;
    T currData;
    int currDataIndex;

    void copy(const FileDataSource&);
    void destroy();
    int countLines() const;
    T convert(const char* str) const;
public:
    FileDataSource(const char*);
    FileDataSource(const FileDataSource&);
    FileDataSource(FileDataSource&&) noexcept;
    FileDataSource& operator=(const FileDataSource&);
    FileDataSource& operator=(FileDataSource&&) noexcept;
    T get()  override;
    Vector<T> getSequence(int) override; 
    bool hasNext() const override;
    bool reset() override; 
    T operator()() override;
    ~FileDataSource();
};

#include "FileDataSource.inl"

#endif