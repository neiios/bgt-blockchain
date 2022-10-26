#include <hash.hpp>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include "block.hpp"
#include "helpers.hpp"
#include "transaction.hpp"
#include "user.hpp"

#define USER_COUNT 1000
#define TRANSACTION_COUNT 10000
#define TRANSACTIONS_IN_BLOCK 100
#define DIFFICULTY_TARGET 3
#define VERSION 1

using namespace std;

int main() {
    Hash h;
    // create 1000 users
    vector<User> users;
    for (int i = 0; i < USER_COUNT; i++) {
        users.emplace_back("user" + to_string(i),
                           generateRandomNumber(100, 1000000));
    }

    // create a pool and place 10000 transaction into it
    // TODO: dont use a vector for a pool. it is really inefficient
    vector<Transaction> pool;
    for (int i = 0; i < TRANSACTION_COUNT; i++) {
        auto firstUser = generateRandomNumber(0, 1000);
        auto secondUser = generateRandomNumber(0, 1000);
        auto transactionAmount = generateRandomNumber(1, 1000);
        pool.emplace_back(h.hashString("user" + to_string(firstUser)),
                          h.hashString("user" + to_string(secondUser)),
                          transactionAmount);
    }

    // create a vector of blocks (a blockchain)
    vector<Block> blockchain;

    // TODO: make it possible for blocks to have less than TRANSACTIONS_IN_BLOCK
    // transaction when there is not enough transactions in a pool
    // TODO: make it work when the number of transactions in a pool and the
    // number of transactions in a block is not evenly divisible
    // TODO: select transactions from the pool randomly
    for (int i = 0; i < TRANSACTION_COUNT / TRANSACTIONS_IN_BLOCK; i++) {
        vector<Transaction> blockTransactions;
        for (int j = 0; j < TRANSACTIONS_IN_BLOCK; j++) {
            // TODO: check the transaction and remove it from the pool if its
            // invalid
            blockTransactions.push_back(pool.at(j));
        }
        // remove transactions from the pool
        pool.erase(pool.begin(), pool.begin() + TRANSACTIONS_IN_BLOCK);

        // TODO: there probably is a better way to create a genesis block
        if (i == 0) {
            blockchain.emplace_back("genesis block", DIFFICULTY_TARGET, VERSION,
                                    blockTransactions);
        } else {
            blockchain.emplace_back(blockchain.at(i - 1).hashBlock(),
                                    DIFFICULTY_TARGET, VERSION,
                                    blockTransactions);
        }

        cout << "Block number " << i << "\nBlock data: \n"
             << blockchain.back() << endl
             << endl;

        // update the user balance after the block has been mined
        updateUserBalance(blockchain.back(), users);
    }

    return 0;
}
