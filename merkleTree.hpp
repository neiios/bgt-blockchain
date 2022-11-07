#pragma once
#include <cstddef>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "defines.hpp"
#include "hash.hpp"
#include "transaction.hpp"

// merkle.cpp
#include <bitcoin/bitcoin.hpp>
// Merkle Root Hash

class MerkleTree {
  private:
    Hash h;
    std::string hashPair(const std::string& a, const std::string& b) {
        std::stringstream s;
        s << a << b;
        return h.hashString(s.str());
    }

    bc::hash_digest create_merkle(bc::hash_list& merkle) {
        // Stop if hash list is empty or contains one element
        if (merkle.empty())
            return bc::null_hash;
        else if (merkle.size() == 1)
            return merkle[0];
        // While there is more than 1 hash in the list, keep looping...
        while (merkle.size() > 1) {
            // If number of hashes is odd, duplicate last hash in the list.
            if (merkle.size() % 2 != 0)
                merkle.push_back(merkle.back());
            // List size is now even.
            assert(merkle.size() % 2 == 0);
            // New hash list.
            bc::hash_list new_merkle;
            // Loop through hashes 2 at a time.
            for (auto it = merkle.begin(); it != merkle.end(); it += 2) {
                // Join both current hashes together (concatenate).
                bc::data_chunk concat_data(bc::hash_size * 2);
                auto concat = bc::serializer<decltype(concat_data.begin())>(
                    concat_data.begin());
                concat.write_hash(*it);
                concat.write_hash(*(it + 1));
                // Hash both of the hashes.
                bc::hash_digest new_root = bc::bitcoin_hash(concat_data);
                // Add this to the new list.
                new_merkle.push_back(new_root);
            }
            // This is the new list.
            merkle = new_merkle;
#ifdef VERBOSE_MERKLE
            std::cout << "Current merkle hash list:" << std::endl;
            for (const auto& hash : merkle)
                std::cout << " " << bc::encode_base16(hash) << std::endl;
            std::cout << std::endl;
#endif
        }
        // Finally we end up with a single item.
        return merkle[0];
    }

  public:
    /**
     * @brief Function to find a merkle root hash
     *
     * @param txs hashes of all transactions in a block
     */
    std::string findMerkleRootHash(const std::vector<std::string>& txs) {
        // a vector to store hashes in a proper format
        bc::hash_list tx_hashes;
        for (const auto& tx : txs) {
            char msg[65];
            strcpy(msg, tx.c_str());
            tx_hashes.push_back(bc::hash_literal(msg));
        }

        // create a merkle root hash
        const bc::hash_digest merkle_root = create_merkle(tx_hashes);
        return bc::encode_hash(merkle_root);
    }
};
