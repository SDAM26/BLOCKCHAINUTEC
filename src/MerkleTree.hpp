
#pragma once

#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>
#include "../structures/CircularList.hpp"

template <typename T>
class MerkleTree {
private:
    std::vector<std::string> hashes;
    std::string root_hash;

public:
    MerkleTree() = default;
    explicit MerkleTree(const CircularList<T>& data);
    std::string getRootHash() const;
    void hasher(const CircularList<T>& data);

private:
    std::string calculateHash(const T& data) const;
    std::string combineHashes(const std::string& hash1, const std::string& hash2) const;
    std::string hashString(const std::string& str) const;
};

template <typename T>
MerkleTree<T>::MerkleTree(const CircularList<T>& data) {
    calculateHash(data);
}

template <typename T>
void MerkleTree<T>::hasher(const CircularList<T>& data) {
    // Calcular los hashes de los datos y almacenarlos en el vector de hashes
    for (const auto& item : data) {
        std::string hash = hasher(item);
        hashes.push_back(hash);
    }

    // Construir el árbol Merkle combinando los hashes
    while (hashes.size() > 1) {
        std::vector<std::string> new_hashes;
        for (std::size_t i = 0; i < hashes.size(); i += 2) {
            if (i + 1 < hashes.size()) {
                std::string combined_hash = combineHashes(hashes[i], hashes[i + 1]);
                new_hashes.push_back(combined_hash);
            } else {
                new_hashes.push_back(hashes[i]);
            }
        }
        hashes = std::move(new_hashes);
    }

    // Establecer el hash raíz final
    root_hash = hashes.empty() ? "" : hashes[0];
}

template <typename T>
std::string MerkleTree<T>::getRootHash() const {
    return root_hash;
}

template <typename T>
std::string MerkleTree<T>::calculateHash(const T& data) const {
    std::ostringstream oss;
    oss << data;
    std::string str = oss.str();
    return hashString(str);
}

template <typename T>
std::string MerkleTree<T>::combineHashes(const std::string& hash1, const std::string& hash2) const {
    std::string combined = hash1 + hash2;
    return hashString(combined);
}

template <typename T>
std::string MerkleTree<T>::hashString(const std::string& str) const {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(str.c_str()), str.length(), digest);

    std::ostringstream oss;
    oss << std::hex << std::setfill('0');
    for (unsigned char c : digest) {
        oss << std::setw(2) << static_cast<int>(c);
    }

    return oss.str();
}
