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
        if (txs.size() == 1)
            return txs.at(0);

        for (size_t i = 0; i < txs.size(); i += 2) {
            // TODO: i can do better than that
            if (i + 1 < txs.size()) {
                tempTxs.push_back(hashPair(txs.at(i), txs.at(i + 1)));
            } else {
                tempTxs.push_back(hashPair(txs.at(i), txs.at(i)));
            }
        }

#ifdef BE_VERBOSE
        std::cout << tempTxs.size() << std::endl;
        for (const auto& tx : tempTxs)
            std::cout << tx << std::endl;
#endif

        return findMerkleRootHash(tempTxs);
    }
};
