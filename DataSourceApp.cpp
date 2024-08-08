#include "GeneratorDataSource.h"
#include "AlternateDataSource.h"
#include "FileDataSource.h"
#include "ArrayDataSource.h"
#include <cstring>
#include <fstream>

int fib(int n) {
    if(n == 0) {
        return 0;
    }
    if (n == 1 || n == 2) {
        return 1;
    }

    return fib(n - 1) + fib(n - 2);
}

int odd(int n) {
    return n % 2 == 0 ? n + 1 : n;
}

int rand(int n) {
    return std::rand() + n;
}

char* generateWord(char* word) {
    word = new char[10];

    for(int i = 0; i < 10; ++i) {
        word[i] = ('a' + std::rand() % 26);
    }
    word[10] = '\0';
    return word;
}

int main() {
    // First sub-task - generating 25 random words with length of 10 lowercase latin letters. 
    char* (*wordsGeneratorFnc)(char*);
    wordsGeneratorFnc = &generateWord;
    DataSource<char*>* charsSrc = new GeneratorDataSource<char*>(wordsGeneratorFnc);
    charsSrc->getSequence(25).print();

    // Second sub-task
    // Creating pointers to helper functions above.
    int (*oddFncPtr)(int);
    oddFncPtr = &odd;
    int (*randFncPtr)(int);
    randFncPtr = &rand;
    int (*fibFncPtr)(int);
    fibFncPtr = &fib;

    // Creating three generators for odd, random and fibonacci numbers.
    DataSource<int>* oddNumbersGen = new GeneratorDataSource<int>(oddFncPtr);
    DataSource<int>* randNumbersGen = new GeneratorDataSource<int>(randFncPtr);
    DataSource<int>* fibonacciGen = new GeneratorDataSource<int>(fibFncPtr);

    // Creating an array of the generators above.
    const int SOURCES_COUNT = 3;
    const int FIBONACCI_SAMPLES_COUNT = 25;
    DataSource<int>* sources[SOURCES_COUNT] = {oddNumbersGen, randNumbersGen, new ArrayDataSource<int>(
        fibonacciGen->getSequence(FIBONACCI_SAMPLES_COUNT).getData(), FIBONACCI_SAMPLES_COUNT)};
    
    // Creating the base alternate generator.
    DataSource<int>* alternateSrc = new AlternateDataSource<int>(sources, SOURCES_COUNT);
    const int SEQUENCE_SAMPLES_COUNT = 1000;
    Vector<int> v = alternateSrc->getSequence(SEQUENCE_SAMPLES_COUNT);
    
    // Typing filename of binary file to store in it the sequence of 1000 samples of alternateSrc and writing in this file.
    std::cout << "Enter binary file name: ";
    const int MAX_FILENAME_LENGTH = 256;
    char* filename = new char [MAX_FILENAME_LENGTH];
    std::cin.getline(filename, MAX_FILENAME_LENGTH);
    std::ofstream out(filename, std::ios::binary | std::ios::app);
    if (!out) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return 1;
    }
    out.write(reinterpret_cast<const char*>(&SEQUENCE_SAMPLES_COUNT), sizeof(SEQUENCE_SAMPLES_COUNT));
    out.write(reinterpret_cast<const char*>(&v), sizeof(v));
    out.close();

    // Reading from this file, fileSrc initialization with the read numbers and printing them.
    DataSource<int>* fileSrc = new FileDataSource<int>(filename);
    fileSrc->getData().print(); 

    // Realising memory.
    delete[] fileSrc;
    delete[] filename;
    delete[] alternateSrc;
    delete[] charsSrc;

    return 0;
}