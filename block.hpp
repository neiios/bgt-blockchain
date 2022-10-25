#pragma once
#include <algorithm>
#include <chrono>
#include <cstdint>
#include <ctime>
#include <iostream>
#include <iterator>
#include <ostream>
#include <string>
#include <vector>
#include "hash.hpp"
#include "transaction.hpp"

class Block {
  private:
    // header
    std::string prevHash;
    uint64_t timestamp;
    uint8_t difTarget;
    uint32_t version;
    // body
    std::vector<Transaction> transactions;
    // header
    std::string rootHash;
    uint64_t nonce = 0;

    std::string findTransactionsHash() {
        std::ostringstream s;
        Hash h;

        // convert vector of transactions to a string
        std::copy(transactions.begin(), transactions.end(),
                  std::ostream_iterator<Transaction>(s));
        return h.hashString(s.str());
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
          rootHash(findTransactionsHash()) {
        Hash h;
        std::string prefix(difTarget, '0');
        std::string hash;
        // actually mine the block
        while (true) {
            // hash the header of a block
            hash = h.hashString(
                prevHash + std::to_string(timestamp) + std::to_string(version) +
                rootHash + std::to_string(nonce) + std::to_string(difTarget));
            if (hash.starts_with(prefix)) {
                break;
            }
            // TODO: nonce may oveflow here
            nonce++;
        }
        std::cout << "the block has been mined, root hash is " << hash
                  << " and nonce is " << nonce << std::endl;
    }

    friend std::ostream& operator<<(std::ostream& os, const Block& b) {
        os << "Previous hash: " << b.prevHash << "\n Timestamp: " << b.timestamp
           << "\n Version: " << b.version << "\n Root Hash: " << b.rootHash
           << "\n Nonce: " << b.nonce << "\n Dif. target: " << b.difTarget
           << std::endl;
        return os;
    }
};
