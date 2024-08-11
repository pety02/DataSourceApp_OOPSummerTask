#pragma once
#ifndef FILEDATASOURCE_INL
#define FILEDATASOURCE_INL

#include "FileDataSource.h"

template <typename T>
inline void FileDataSource<T>::copy(const FileDataSource<T>& other) {
    this->filename = new char[std::strlen(other.filename) + 1];
    this->filename = std::strcpy(this->filename, other.filename);
    this->data = other.data;
    this->currData = other.currData;
    this->currDataIndex = other.currDataIndex;
}

template <typename T>
inline void FileDataSource<T>::destroy() {
    delete[] this->filename;
}

template <typename T>
inline int FileDataSource<T>::countLines() const
{
    std::ifstream file(this->filename); 
    if (!file.is_open()) { 
        throw std::runtime_error("Cannot open file!");
    }

    const int BUFFER_mAX_SIZE = 256; 
    char line[BUFFER_mAX_SIZE];
    int linesCounter = 0; 
    while(file.getline(line, BUFFER_mAX_SIZE)) {
        linesCounter++;
    }

    file.close();
    return linesCounter;
}

template <typename T>
inline T FileDataSource<T>::convert(const char *str) const
{
    assert(str != nullptr); 

    if (std::is_same<T, int>::value || std::is_same<T, unsigned int>::value
    || std::is_same<T, long>::value || std::is_same<T, long long>::value
    || std::is_same<T, unsigned long>::value || std::is_same<T, unsigned long long>::value) {
        return std::atoi(str);
    } 
    else if (std::is_same<T, float>::value || std::is_same<T, double>::value || std::is_same<T, long double>::value) {
        return std::atof(str);
    } 
    else if (std::is_same<T, bool>::value) {
        return std::strcmp(str, "true") == 0 || std::strcmp(str, "1") == 0; 
    } else if (std::is_same<T, char*>::value) {
        return *str;
    } else {
        throw std::invalid_argument("Unsupported type conversion requested");
    }
}

template <typename T>
inline FileDataSource<T>::FileDataSource(const char* filename) {
    this->filename = new char[std::strlen(filename) + 1];
    this->filename = std::strcpy(this->filename, filename);
    this->currData = T();
    this->currDataIndex = 0;
}

template <typename T>
inline FileDataSource<T>::FileDataSource(const FileDataSource<T>& other) {
    this->copy(other);
}

template <typename T>
inline FileDataSource<T>::FileDataSource(FileDataSource<T>&& other) noexcept {
    this->copy(other);
    other.filename = nullptr;
}

template <typename T>
inline FileDataSource<T>& FileDataSource<T>::operator=(const FileDataSource<T>& other) {
    if(this != &other) {
        this->destroy();
        this->copy(other);
    }

    return *this;
}

template <typename T>
inline FileDataSource<T>& FileDataSource<T>::operator=(FileDataSource&& other) noexcept {
    if(this != &other) {
        this->destroy();
        this->copy(other);

        other.filename = nullptr;
    }

    return *this;
}

template <typename T>
inline T FileDataSource<T>::get() {
    if(!this->hasNext()) {
        throw std::out_of_range("No more elements to be read!");
    }
    std::ifstream file(this->filename); 
    if (!file.is_open()) { 
        throw std::runtime_error("Cannot open file!");
    }

    const int BUFFER_mAX_SIZE = 256; 
    char line[BUFFER_mAX_SIZE];
    int linesNumber = this->currDataIndex;
    int currentLine = 0;

    while (file.getline(line, BUFFER_mAX_SIZE)) {
        if (currentLine == linesNumber) {
            try {
                this->currData = this->convert(line);
                this->currDataIndex++;
                return this->currData; 
            } catch(std::invalid_argument& ex) {
                throw ex;
            }
        }

        currentLine++;
    }

    file.close(); 
    throw std::out_of_range("No more elements to be read!");
}

template <typename T>
inline Vector<T> FileDataSource<T>::getSequence(int count) {
    Vector<T> sequence = Vector<T>();
    for(int i = 0; i < count; ++i) {
        try {
            this->currData = this->get();
            sequence.append(this->currData);
        } catch (std::out_of_range&) {
            break;
        }
    }

    return sequence;
}

template <typename T>
inline bool FileDataSource<T>::hasNext() const {
    try {
        bool _hasNext = this->currDataIndex < this->countLines();
        return _hasNext;
    } catch(std::runtime_error&) {
        return false;
    }
}

template <typename T>
inline bool FileDataSource<T>::reset() {
    return true;
}

template <typename T>
inline T FileDataSource<T>::operator()() {
    return this->get();
}

template <typename T>
inline FileDataSource<T>::~FileDataSource() {
    this->destroy();
}

#endif