#pragma once
#ifndef FILEDATASOURCE_INL
#define FILEDATASOURCE_INL

#include "FileDataSource.h"

template<typename T>
inline void FileDataSource<T>::copy(const FileDataSource<T>& other)
{
    this->data = other.data;
    this->miniedData = other.miniedData;
    this->currDataIndex = other.currDataIndex;
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
    this->miniedData = Vector<T>();
    this->currDataIndex = 0;
    this->filename = nullptr;
}

template <typename T>
inline FileDataSource<T>::FileDataSource(const char* filename)
{
    this->data = Vector<T>();
    this->miniedData = Vector<T>();
    this->currDataIndex = 0;
    this->filename = new char[std::strlen(filename) + 1];
    this->filename = std::strcpy(this->filename, filename);

    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    int dataCount;
    file.read(reinterpret_cast<char*>(&dataCount), sizeof(dataCount));
    file.read(reinterpret_cast<char*>(&this->data), sizeof(this->data));
    this->currDataIndex += this->data.size();

    file.close();
}

template <typename T>
inline FileDataSource<T>::FileDataSource(const FileDataSource<T>& other)
{
    this->copy(other);
}

template <typename T>
inline FileDataSource<T>::FileDataSource(FileDataSource<T>&& other) noexcept
{
    this->copy(other);
    other.data = Vector<T>();
    other.miniedData = Vector<T>();
    other.currDataIndex = 0;
    other.filename = nullptr;
}

template <typename T>
inline FileDataSource<T>& FileDataSource<T>::operator=(const FileDataSource<T>& other)
{
    if(this != &other) {
        this->destroy();
        this->copy(other);
    }

    return *this;
}

template <typename T>
inline FileDataSource<T>& FileDataSource<T>::operator=(FileDataSource<T>&& other) noexcept
{
    if(this != &other) {
        this->destroy();
        this->copy(other);
        other.data = Vector<T>();
        other.miniedData = Vector<T>();
        other.currDataIndex = 0;
        other.filename = nullptr;
    }

    return *this;
}

template<typename T>
inline FileDataSource<T>::~FileDataSource()
{
    this->destroy();
}

template <typename T>
inline Vector<T> FileDataSource<T>::getSequence(int count)
{
    int minCount = std::min(this->data.size(), count);
    for (int i = 0; i < minCount; ++i) {
        this->miniedData.append(this->data[i]);
        this->currDataIndex++;
    }

    return this->miniedData;
}

#endif
