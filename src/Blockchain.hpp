
#pragma once

#include <fstream>
#include <sstream>
#include <chrono>
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
    void createBlock();
    void clear();
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
    const std::string BASE_DIR = "../data/";
    const int LINES_LIMIT = 10;

    std::string csvFilePath = BASE_DIR + filename; 
    std::ifstream file(csvFilePath);

    if (!file) {
        throw "Error opening file.";
    }

    createBlock();

    std::string line{};
    int currentLine = 1;
    while (std::getline(file, line) && currentLine < LINES_LIMIT) {
        std::istringstream iss(line);
        std::string sender, recipient, date, amout_str;
        
        std::getline(iss, sender, ',');
        std::getline(iss, recipient, ',');
        std::getline(iss, amout_str, ',');
        std::getline(iss, date);

        T transaction(sender, recipient, std::stod(amout_str), date);
        ++currentLine;
        data.push_back(transaction);
    }

    file.close();

   
}
template <typename T>
void Blockchain<T>::createBlock() {
    // Esperar el tiempo especificado
    std::this_thread::sleep_for(duration);

    // Crear un nuevo bloque y realizar las operaciones necesarias
    Block<T>* newBlock = new Block<T>();
    // Agregar el bloque a la cadena de bloques
    addBlock(newBlock);

    // Realizar otras acciones después de la creación del bloque, si es necesario

}

template <typename T>
size_t Blockchain<T>::getNumBlocks() const {
    return blocks;
}

template <typename T>
void Blockchain<T>::clear() {

}
