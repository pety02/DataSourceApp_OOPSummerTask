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

    void copy(const FileDataSource<T>&);
    void destroy();

    FileDataSource();
public:
    FileDataSource(const char*);
    FileDataSource(const FileDataSource&);
    FileDataSource(FileDataSource&&) noexcept;
    FileDataSource& operator=(const FileDataSource&);
    FileDataSource& operator=(FileDataSource&&) noexcept;
    ~FileDataSource();

    Vector<T> getSequence(int) override;
};

#include "FileDataSource.inl"

#endif 