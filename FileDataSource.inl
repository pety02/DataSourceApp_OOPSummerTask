#pragma once
#ifndef FILEDATASOURCE_INL
#define FILEDATASOURCE_INL

#include "FileDataSource.h"

template<typename T>
inline void FileDataSource<T>::copy(const FileDataSource<T>& other)
{
    this->data = other.data;
    this->filename = new char[std::strlen(other.filename) + 1];
    this->filename = std::strcpy(this->filename, other.filename);
}

template<typename T>
inline void FileDataSource<T>::destroy()
{
    delete[] this->filename;
}

template<typename T>
inline FileDataSource<T>::FileDataSource()
{
    this->data = Vector<T>();
    this->filename = nullptr;
}

template <typename T>
inline FileDataSource<T>::FileDataSource(const char* filename)
{
    //this->data = Vector<T>();
    this->filename = new char[std::strlen(filename) + 1];
    this->filename = std::strcpy(this->filename, filename);

    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    int dataCount;
    file.read(reinterpret_cast<char*>(&dataCount), sizeof(dataCount));
    file.read(reinterpret_cast<char*>(&this->data), sizeof(this->data));

    file.close();
}

template<typename T>
inline FileDataSource<T>::~FileDataSource()
{
    this->destroy();
}

template <typename T>
inline Vector<T> FileDataSource<T>::getSequence(int count)
{
    Vector<T> current = Vector<T>();
    int minCount = std::min(this->data.size(), count);
    for (int i = 0; i < minCount; ++i) {
        current.append(this->data[i]);
        this->currDataIndex++;
    }
    return current;
}

#endif
