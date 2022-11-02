#pragma once
#include <cstddef>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "defines.hpp"
#include "hash.hpp"
#include "transaction.hpp"

class MerkleTree {
  private:
    Hash h;
    std::string hashPair(const std::string& a, const std::string& b) {
        std::stringstream s;
        s << a << b;
        return h.hashString(s.str());
    }

  public:
    /**
     * @brief Function to find a merkle root hash
     *
     * @param txs hashes of all transactions in a block
     */
    std::string findMerkleRootHash(const std::vector<std::string>& txs) {
        std::vector<std::string> tempTxs;
        // base case
        if (txs.size() == 1) {
#ifdef VERBOSE_MERKLE
            std::cout << "Root hash: " << txs.at(0) << std::endl;
#endif
            return txs.at(0);
        }

#ifdef VERBOSE_MERKLE
        std::cout << "Current level (hash count): " << txs.size() << " ";
        for (const auto& tx : txs)
            std::cout << tx << " ";
        std::cout << std::endl;
#endif

        for (size_t i = 0; i < txs.size(); i += 2) {
            if (i + 1 < txs.size()) {
                tempTxs.push_back(hashPair(txs.at(i), txs.at(i + 1)));
            } else {
                tempTxs.push_back(hashPair(txs.at(i), txs.at(i)));
            }
        }

        return findMerkleRootHash(tempTxs);
    }
};
