#pragma once
#ifndef FILEDATASOURCE_H
#define FILEDATASOURCE_H

#include <fstream>
#include <cstring>
#include "DataSource.h"

template <typename T>
class FileDataSource final : public DataSource<T> {
private:
    char* filename;

protected:
    void copy(const FileDataSource<T>&);
    void destroy();

    FileDataSource();
public:
    FileDataSource(const char*);
    ~FileDataSource();

    Vector<T> getSequence(int) override;
};

#include "FileDataSource.inl"

#endif 

