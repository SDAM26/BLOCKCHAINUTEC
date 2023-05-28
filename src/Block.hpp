
#pragma once

#include <iostream>
#include <sstream>
#include <ctime>
#include <vector>
#include <chrono>
#include <iomanip>
#include <openssl/sha.h>

#include "MerkleTree.hpp"
#include "../structures/BankTransfer.hpp"
#include "../structures/CircularList.hpp"

template <typename T>
class Block {
private:
    static const int MAX_REGISTERS;

    std::time_t time_stamp; // block time stamp
    std::string actual_hash; // stores actual hash
    std::string prev_hash; // stores hash for previous block
    CircularList<T> data;
    MerkleTree<T> root; 
    int nonce; 
    int id;

public:
    Block();
    void addRegister(const T& reg); 
    void removeRegister(int index); 
    T getRegister(int index) const; 
    bool validateHash() const; 
    void mineBlock(); 

private:
    void adjustDifficulty(int& targetDifficulty, long elapsedTime); //
    std::string calculateHash() const; //
    bool meetsTargetDifficulty(const std::string& hash, int targetDifficulty); //
};

// ---------------------------------------------------------------------------------------------

template <typename T>
const int Block<T>::MAX_REGISTERS = 10;

template<typename T>
Block<T>::Block() {
    mineBlock();

}

// Proof of work
template <typename T>
void Block<T>::mineBlock() {
    root.hasher(data);
    int targetDifficulty = 2; // Dificultad objetivo (número de ceros consecutivos al inicio del hash)
    int adjustmentInterval = 3; // Intervalo de ajuste de dificultad (en número de bloques)
    int blocksSinceAdjustment = 0; // Contador de bloques desde el último ajuste

    auto startTime = std::chrono::steady_clock::now();
    std::string hash;
    do {
        nonce++;
        hash = calculateHash();
    } while (!meetsTargetDifficulty(hash, targetDifficulty));

    auto endTime = std::chrono::steady_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

    actual_hash = hash; // Actualizar el hash del bloque después de encontrar el nonce válido

    std::cout << "Block mined in " << elapsedTime << " ms" << std::endl;
    std::cout << "Hash: " << actual_hash << std::endl;
    std::cout << "Nonce: " << nonce << std::endl;

    blocksSinceAdjustment++;
    if (blocksSinceAdjustment >= adjustmentInterval) {
        adjustDifficulty(targetDifficulty, elapsedTime);
        blocksSinceAdjustment = 0;
    }
}

template <typename T>
void Block<T>::adjustDifficulty(int& targetDifficulty, long elapsedTime) {
    if (elapsedTime < 1000) {
        targetDifficulty++;
    } else if (elapsedTime > 3000 && targetDifficulty > 1) {
        targetDifficulty--;
    }
}

template <typename T>
std::string Block<T>::calculateHash() const {
    std::stringstream ss;
    ss << prev_hash << time_stamp << nonce << root.getRootHash();
  
    // Calcular el hash SHA-256 utilizando OpenSSL
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(ss.str().c_str()), ss.str().size(), hash);
    
    // Convertir el hash binario a una cadena hexadecimal
    std::stringstream hash_ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        hash_ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }
    
    return hash_ss.str();
}

template <typename T>
bool Block<T>::meetsTargetDifficulty(const std::string& hash, int targetDifficulty) {
    std::string prefix(targetDifficulty, '0');
    return hash.substr(0, targetDifficulty) == prefix;
}

template <typename T>
void Block<T>::addRegister(const T& reg) {
    data.push_back(reg);
}

template <typename T>
T Block<T>::getRegister(int index) const {
    if (index < 0 || index >= data.size()) {
        throw std::out_of_range("Invalid index");
    }
    return data[index];
}

template <typename T>
bool Block<T>::validateHash() const {
    std::string calculatedHash = calculateHash();
    return (actual_hash == calculatedHash);
}


