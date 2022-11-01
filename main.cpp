#include <hash.hpp>
#include <iostream>
#include <list>
#include <random>
#include <string>
#include <vector>
#include "block.hpp"
#include "defines.hpp"
#include "helpers.hpp"
#include "merkleTree.hpp"
#include "transaction.hpp"
#include "user.hpp"

using namespace std;

int main() {
    Hash h;
    // create 1000 users
    vector<User> users;
    for (int i = 0; i < USER_COUNT; i++) {
        users.emplace_back("user" + to_string(i),
                           generateRandomNumber(100, 1000));
    }

#ifdef BE_VERBOSE
    for (const auto& u : users) {
        cout << u << endl;
    }
#endif

    // create a pool and place 10000 transaction into it
    vector<Transaction> pool;
    for (int i = 0; i < TRANSACTION_COUNT; i++) {
        auto firstUser = generateRandomNumber(0, USER_COUNT);
        auto secondUser = generateRandomNumber(0, USER_COUNT);
        auto transactionAmount = generateRandomNumber(10, 100);
        pool.emplace_back(h.hashString("user" + to_string(firstUser)),
                          h.hashString("user" + to_string(secondUser)),
                          transactionAmount);
    }

#ifdef BE_VERBOSE
    for (const auto& tr : pool) {
        cout << tr << endl;
    }
#endif

    // create a vector of blocks (a blockchain)
    vector<Block> blockchain;

    // TODO: select transactions from the pool randomly
    while (!pool.empty()) {
        vector<Transaction> blockTransactions;

        // add transactions from a pool to a new block
        while (blockTransactions.size() < TRANSACTIONS_IN_BLOCK &&
               !pool.empty()) {
            // check if senders balance is more or equal to transaction amount
            auto sender = findUser(users, pool.front().getSender());
            if (sender->getBalance() < pool.front().getAmount()) {
                // remove the transaction and skip to the next one
                pool.erase(pool.begin());
                continue;
            }

            blockTransactions.push_back(pool.front());
            // update the user balance temporarily
            // updateUserBalance(pool.front(), usersTemp);
            pool.erase(pool.begin());
        }

        // TODO: there probably is a better way to create a genesis block
        if (blockchain.size() == 0) {
            blockchain.emplace_back("genesis block", DIFFICULTY_TARGET, VERSION,
                                    blockTransactions);
        } else {
            blockchain.emplace_back(
                blockchain.at(blockchain.size() - 1).hashBlock(),
                DIFFICULTY_TARGET, VERSION, blockTransactions);
        }

#ifdef BE_VERBOSE
        cout << "Block number " << blockchain.size()
             << "\nBlock data:" << blockchain.back() << endl;
#endif

        // update the user balance after the block has been mined
        for (const Transaction& transaction :
             blockchain.back().getTransactions()) {
            updateUserBalance(transaction, users);
        }
    }

#ifdef BE_VERBOSE
    for (const auto& user : users) {
        cout << user << endl;
    }
#endif

    return 0;
}
