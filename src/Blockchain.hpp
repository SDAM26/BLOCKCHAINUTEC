#pragma once

#include <fstream>
#include "Block.hpp"

template <typename T>
class Blockchain {
private:
    Block<T>* genesis;
    size_t blocks;
public:
    Blockchain();
    Blockchain(Block<T>* block);
    ~Blockchain();
    
    Block<T>* getBlock(std::string hash) const;
    size_t getNumBlocks() const;
    void addBlock(Block<T>* block);
    void editBlock(Block<T>* block);
    void loadFromFile(std::string filename);
    void saveToFile(std::string filename);
};

//--------------------------------------------------------------

template <typename T>
Blockchain<T>::Blockchain() 
    : genesis{}, blocks{} 
{}

template <typename T> 
Blockchain<T>::Blockchain(Block<T>* genesis)
    : genesis{genesis}, blocks{}
{}

template <typename T>
Blockchain<T>::~Blockchain() { 
    clear(); 
}

template <typename T>
void Blockchain<T>::addBlock(Block<T>* block) {

    ++blocks;
}

template <typename T>
void Blockchain<T>::saveToFile(std::string filename) {
    // Lógica para guardar la cadena de bloques en un archivo
}

template <typename T>
void Blockchain<T>::loadFromFile(std::string filename) {
   
}

template <typename T>
size_t Blockchain<T>::getNumBlocks() const {
    return blocks;
}

