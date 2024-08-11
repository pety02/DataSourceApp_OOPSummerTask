#include "GeneratorDataSource.h"
#include "AlternateDataSource.h"
#include "FileDataSource.h"
#include "DefaultDataSource.h"
#include "ArrayDataSource.h"

int nextNumHelper(int n) {
    return n + 1;
}

Vector<int> nextNum(int cnt) {
    Vector<int> nums = Vector<int>();
    for(int i = 0; i < cnt; ++i) {
        nums.append(nextNumHelper(i));
    }

    return nums;
}

int main() {
    char txtFilename[] = "numbers.txt";
    std::ofstream txtOut(txtFilename);
    if(!txtOut) {
        std::cerr << "Failed to open file: " << txtFilename << std::endl;
        return 1;
    }
    for(int i = 0; i < 15; ++i) {
        txtOut << i << std::endl;
    }

    // Vector tests:
    Vector<int>* data = new Vector<int>();
    for(int i = 0; i < 10; ++i) {
        data->append(i + 1);
    } 
    std::cout << "data:" << std::endl;
    for(int i = 0; i < 10; ++i) {
        if(i == 9) {
            std::cout << (*data)[i] << std::endl;
            break;
        }
        std::cout << (*data)[i] << ", ";
    } 

    for(int i = 0; i < 10; ++i) {
        (*data)[i] = i + 11; 
    } 
    std::cout << "modified data:" << std::endl;
    for(int i = 0; i < 10; ++i) {
        if(i == 9) {
            std::cout << (*data)[i] << std::endl;
            break;
        }
        std::cout << (*data)[i] << ", ";
    } 

    for(int i = 0; i < 10; ++i) {
        if(i == 5) {
            data->remove(i);
        }
    }
    std::cout << "Vector size = " << data->size() << std::endl;
    data->print();

    Vector<int>* copy = new Vector<int>(*data);
    std::cout << "Copy vector data:" << std::endl;
    copy->print();

    Vector<int>* copy2 = data;
    std::cout << "Second copy vector data:" << std::endl;
    copy2->print();

    Vector<int>* copy3 = new Vector<int>(std::move(*data));
    std::cout << "Third copy vector data:" << std::endl;
    copy3->print();

    Vector<int> copy4 = std::move(*copy3);
    std::cout << "Fourth copy vector data:" << std::endl;
    copy4.print();
    int* dataToArr = copy4.getData();
    std::cout << "array data: " << std::endl;
    for(int i = 0; i < data->size(); ++i) {
        std::cout << dataToArr[i] << " ";
    }

    // Default Data Source tests:
    DefaultDataSource<bool>* defSrc = new DefaultDataSource<bool>();
    std::cout << "Default numbers: " << std::endl;
    defSrc->getSequence(10).print();
    bool zero = defSrc->get();
    bool defSrcHasNext = defSrc->hasNext();
    bool defSrcCanReset = defSrc->reset();
    bool otherZero = (*defSrc)();
    bool defSrcToBool = (bool)(*defSrc);
    std::cout << "Results: " << std::boolalpha << zero << " " << std::boolalpha << defSrcHasNext << " "
    << std::boolalpha << defSrcCanReset << " " << std::boolalpha << defSrcToBool << " " << std::boolalpha << otherZero << std::endl;
    
    // Array Data Source tests:
    ArrayDataSource<int>* arrSrc = new ArrayDataSource<int>(dataToArr, 10);
    std::cout << "Numbers from array: " << std::endl;
    arrSrc->getSequence(5).print();
    int numFromArr = arrSrc->get();
    bool arrSrcHasNext = arrSrc->hasNext();
    bool arrSrcCanReset = arrSrc->reset();
    int otherNumFromArr = (*arrSrc)();
    bool arrSrcToBool = (bool)(*arrSrc);
    std::cout << "Results: " << numFromArr << " " <<  std::boolalpha << arrSrcHasNext 
    << " " << std::boolalpha << arrSrcCanReset << " " << std::boolalpha << arrSrcToBool 
    << " " << otherNumFromArr << std::endl;

    // File Data Source tests:
    FileDataSource<int>* fileSrc = new FileDataSource<int>("numbers.txt");
    std::cout << "Numbers from file: " << std::endl;
    fileSrc->getSequence(6).print();
    int numFromFile = fileSrc->get();
    bool fileSrcHasNext = fileSrc->hasNext();
    bool fileSrcCanReset = fileSrc->reset();
    int otherNumFromFile = (*fileSrc)();
    bool fileSrcToBool = (bool)(*fileSrc);
    FileDataSource<int>* fileSrc2 = new FileDataSource<int>(*fileSrc);
    FileDataSource<int>* fileSrc3 = new FileDataSource<int>(std::move(*fileSrc));
    FileDataSource<int>* fileSrc4 = fileSrc3;
    FileDataSource<int>* fileSrc5 = std::move(fileSrc4);
    std::cout << "Results: " << numFromFile << " " << std::boolalpha << fileSrcCanReset 
    << " " << std::boolalpha << fileSrcHasNext << " " << std::boolalpha << fileSrcToBool << " " 
    << otherNumFromFile << std::endl;

    // Alternate Data Source tests:
    DataSource<int>** srcs = new DataSource<int>*[2] {arrSrc, fileSrc4};
    AlternateDataSource<int>* altSrc = new AlternateDataSource<int>(srcs, 2);
    std::cout << "Numbers from alternate data source: " << std::endl;
    altSrc->getSequence(3).print();
    int numFromAlt = altSrc->get();
    bool altSrcHasNext = altSrc->hasNext();
    bool altSrcCanReset = altSrc->reset();
    int otherNumFromAlt = (*altSrc)();
    bool altSrcToBool = (bool)(*altSrc);
    AlternateDataSource<int>* altSrc2 = new AlternateDataSource<int>(*altSrc);
    AlternateDataSource<int>* altSrc3 = new AlternateDataSource<int>(std::move(*altSrc));
    AlternateDataSource<int>* altSrc4 = altSrc3;
    AlternateDataSource<int>* altSrc5 = std::move(altSrc4);
    std::cout << "Results: " << numFromAlt << " " << std::boolalpha << altSrcHasNext 
    << " " << std::boolalpha << altSrcCanReset << " " << std::boolalpha << altSrcToBool << " " 
    << otherNumFromAlt << std::endl;

    // Generator Data Source tests:
    Vector<int>(*lambdaFnc)(int);
    lambdaFnc = &nextNum;
    GeneratorDataSource<int>* genSrc = new GeneratorDataSource<int>(lambdaFnc);
    std::cout << "Numbers from generator: " << std::endl;
    genSrc->getSequence(6).print();
    int numFromGen = genSrc->get();
    bool genSrcHasNext = genSrc->hasNext();
    bool genSrcCanReset = genSrc->reset();
    int otherNumFromGen = (*genSrc)();
    bool genSrcToBool = (bool)(*genSrc);
    std::cout << "Results: " << numFromGen << " " << std::boolalpha << genSrcCanReset 
    << " " << std::boolalpha << genSrcHasNext << " " << std::boolalpha << genSrcToBool << " " 
    << otherNumFromGen << std::endl;

    // Releasing memory:
    delete genSrc;
    delete altSrc5;
    delete altSrc4;
    delete altSrc3;
    delete altSrc2;
    delete altSrc;
    delete fileSrc5;
    delete fileSrc4;
    delete fileSrc3;
    delete fileSrc2;
    delete fileSrc;
    delete arrSrc;
    delete defSrc;
    delete copy3;
    delete copy2;
    delete copy;
    delete data;
    
    return 0;
}