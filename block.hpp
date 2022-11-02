#pragma once
#include <algorithm>
#include <chrono>
#include <cstdint>
#include <ctime>
#include <iostream>
#include <iterator>
#include <list>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>
#include "defines.hpp"
#include "hash.hpp"
#include "merkleTree.hpp"
#include "transaction.hpp"

class Block {
  private:
    // header
    std::string prevHash;
    uint64_t timestamp;
    uint32_t difTarget;
    uint32_t version;
    // body
    std::vector<Transaction> transactions;
    // header
    std::string rootHash;
    uint64_t nonce = -1;

    std::string findRootHash() {
        std::vector<std::string> hashes;
        // find the hashes of each transaction
        std::transform(transactions.begin(), transactions.end(),
                       std::back_inserter(hashes), [](const Transaction& t) {
                           Hash h;
                           std::ostringstream os;
                           os << t;
                           return h.hashString(os.str());
                       });
        // find merkle root hash
        MerkleTree m;
#ifdef VERBOSE_MERKLE
        std::cout
            << "\nConstructing a merkle tree and finding its root hash...\n";
#endif
        return m.findMerkleRootHash(hashes);
    }

  public:
    Block(const std::string& ph,
          uint32_t dt,
          uint32_t v,
          const std::vector<Transaction>& tr)
        : prevHash(ph),
          timestamp(
              std::chrono::system_clock::now().time_since_epoch().count()),
          difTarget(dt),
          version(v),
          transactions(tr),
          rootHash(findRootHash()) {}

    /**
     * @brief Function that finds a nonce so that a block hash start with n
     * zeros
     *
     */
    void mine(const bool& finishedMining) {
        Hash h;
        std::string prefix(difTarget, '0');
        // actually mine the block
        while (true) {
#pragma omp flush(finishedMining)
            if (finishedMining)
                return;
            nonce++;
            // hash the header of a block
            std::string hash = h.hashString(
                prevHash + std::to_string(timestamp) + std::to_string(version) +
                rootHash + std::to_string(nonce) + std::to_string(difTarget));
            if (hash.starts_with(prefix)) {
                break;
            }
        }
    }

    /**
     * @brief Checks the hash of the block
     *
     */
    std::string hashBlock() const {
        Hash h;
        return h.hashString(prevHash + std::to_string(timestamp) +
                            std::to_string(version) + rootHash +
                            std::to_string(nonce) + std::to_string(difTarget));
    }

    const std::vector<Transaction>& getTransactions() const {
        return transactions;
    }

    friend std::ostream& operator<<(std::ostream& os, const Block& b) {
        os << "Previous block hash: " << b.prevHash
           << "\nTimestamp: " << b.timestamp << "\nVersion: " << b.version
           << "\nRoot Hash: " << b.rootHash << "\nNonce: " << b.nonce
           << "\nDif. target: " << b.difTarget
           << "\nBlock hash: " << b.hashBlock()
           << "\nTransaction count: " << b.transactions.size()
           << "\nBlock data as it was used for hashing: "
           << b.prevHash + std::to_string(b.timestamp) +
                  std::to_string(b.version) + b.rootHash +
                  std::to_string(b.nonce) + std::to_string(b.difTarget);

        return os;
    }
};
