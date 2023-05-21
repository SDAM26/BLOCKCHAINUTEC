#pragma once

#include <iostream>
#include <openssl/sha.h>

template <typename T>
class Block {
public:
   Block<T>* prev; // pointer to the previous block
   std::time_t timestamp; // block timestamp
   uint64_t nonce; // nonce for current block
   std::string actual_hash; // stores actual hash
   std::string prev_hash; // stores hash for previous block
   MerkleTree<T> root; // root hash
   std::vector<T> data;// data for current block

   Block();
   void calculateHash() const;
   bool validateHash() const;
   void addData(const T& transaction); 
   T getData(int index) const;
};


