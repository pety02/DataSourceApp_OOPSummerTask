#include "GeneratorDataSource.h"
#include "AlternateDataSource.h"
#include "FileDataSource.h"
#include "ArrayDataSource.h"
#include <cstring>
#include <fstream>

int fibHelper(int n) {
    if(n == 0) {
        return 0;
    }
    if (n == 1 || n == 2) {
        return 1;
    }

    return fibHelper(n - 1) + fibHelper(n - 2);
}

Vector<int> fib(int count) {
    Vector<int>* v = new Vector<int>();
    int initial = 0;
    while(initial < count) {
        v->append(fibHelper(initial));
        initial++;
    }

    return *v;
}

int oddHelper(int n) {
    return n % 2 == 0 ? n + 1 : n + 2;
}

Vector<int> odd(int count) {
    Vector<int>* v = new Vector<int>();
    int initial = 0, counter = 0;
    while(counter < count) {
        if(initial % 2 == 0) {
            initial += 1;
        } else {
            initial += 2;
        }

        if(v->size() == 0) {
            v->append(initial);
            counter++;
        }
        int lastIndex = v->size() - 1;
        if((*v)[lastIndex] < initial) {
            v->append(initial);
            counter++;
        }
    }

    return *v;
}

int randHelper(int n) {
    return std::rand() + n;
}

Vector<int> rand(int count) {
    Vector<int>* v = new Vector<int>();
    for(int i = 0; i < count; ++i) {
        v->append(randHelper(i));
    }

    return *v;
}

char* generateWordHelper(char* word) {
    word = new char[10];

    for(int i = 0; i < 10; ++i) {
        word[i] = ('a' + std::rand() % 26);
    }
    word[10] = '\0';
    return word;
}

Vector<char*> generateWord(int count) {
    Vector<char*>* v = new Vector<char*>();
    for(int i = 0; i < count; ++i) {
        char* currWord = new char[10];
        v->append(generateWordHelper(currWord));
    }

    return *v;
}

int main() { 
    // First sub-task - generating 25 random words with length of 10 lowercase latin letters. 
    Vector<char*> (*wordsGeneratorFnc)(int);
    wordsGeneratorFnc = &generateWord;
    DataSource<char*>* charsSrc = new GeneratorDataSource<char*>(wordsGeneratorFnc);
    charsSrc->getSequence(25).print();

    // Second sub-task
    // Creating pointers to helper functions above.
    Vector<int> (*oddFncPtr)(int);
    oddFncPtr = &odd;
    Vector<int> (*randFncPtr)(int);
    randFncPtr = &rand;
    Vector<int> (*fibFncPtr)(int);
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
    std::cout << "size = " << v.size() << std::endl;
    // Typing filename of binary file to store in it the sequence of 1000 samples of alternateSrc and writing in this file.
    std::cout << "Enter binary file name: ";
    const int MAX_FILENAME_LENGTH = 256;
    char* filename = new char [MAX_FILENAME_LENGTH];
    std::cin.getline(filename, MAX_FILENAME_LENGTH);
    std::ofstream out(filename, std::ios::binary);
    if (!out) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return 1;
    }
    out.write(reinterpret_cast<const char*>(&SEQUENCE_SAMPLES_COUNT), sizeof(SEQUENCE_SAMPLES_COUNT));
    out.write(reinterpret_cast<const char*>(&v), sizeof(v));
    out.close();

    // Reading from this file, fileSrc initialization with the read numbers and printing them.
    DataSource<int>* fileSrc = new FileDataSource<int>(filename);
    std::cout << "vector length: " << fileSrc->getData().size() << std::endl;
    fileSrc->getData().print(); 

    // Realising memory.
    delete charsSrc;
    delete fileSrc;
    delete alternateSrc;
    delete fibonacciGen;
    delete randNumbersGen;
    delete oddNumbersGen;
    delete[] filename;

    return 0;
}