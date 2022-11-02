#pragma once
#include <algorithm>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include "block.hpp"
#include "defines.hpp"
#include "hash.hpp"
#include "helpers.hpp"
#include "transaction.hpp"
#include "user.hpp"

class Blockchain {
  private:
    std::vector<User> users;
    // the main chain of block (immutable)
    std::vector<Block> blockchain;
    // pool of transactions that need to be handled
    std::vector<Transaction> pool;

    /**
     * @brief Finds a user inside the users vector by username
     *
     * @param vector of users
     * @param username which user to find
     * @return iterator to the user
     */
    auto findUserByUsername(std::vector<User>& us,
                            const std::string& username) {
        return std::find_if(us.begin(), us.end(), [&username](User u) {
            return u.getUsername() == username;
        });
    }

    /**
     * @brief Finds a user inside the users vector by their public key
     *
     * @param vector of users
     * @param pk public key of a user
     * @return iterator to the user
     */
    auto findUserByPk(std::vector<User>& us, const std::string& pk) {
        return std::find_if(us.begin(), us.end(),
                            [&pk](User u) { return u.getPublicKey() == pk; });
    }

    /**
     * @brief Selects a random transaction from a pool
     *
     * @return iterator to the transaction
     */
    auto selectRandomTransaction() {
        auto shift = generateRandomNumber(0, pool.size() - 1);
        return pool.begin() + shift;
    }

    /**
     * @brief Adds transaction to a new block. Checks and updates user balance
     * as well.
     *
     * @param us vector of users. Used to find sender and check balance.
     * @param candidates vector of candidate transactions that will be added to
     * a new block.
     */
    void addTransactionToNewBlock(std::vector<User>& us,
                                  std::vector<Transaction>& candidates);

    /**
     * @brief Returns the last block hash
     *
     */
    std::string getLastBlockHash() {
        if (blockchain.empty())
            return "aed9eeb06430b81abaa9bc6d8025ccfece326f06098bb1589dfd8c3ba08"
                   "e493b";
        return blockchain.back().hashBlock();
    }

    bool checkBlockHash(const Block& b) {
        const std::string prefix(DIFFICULTY_TARGET, '0');
        return b.hashBlock().starts_with(prefix);
    }

    /**
     * @brief Removes transaction in a mined block from a pool
     *
     * @param block mined block
     */
    void removeTransactions(const Block& block);

    /**
     * @brief Updates user balance with transactions from a new block
     *
     * @param b newly mined block
     */
    void updateUserBalance(std::vector<User>& us, const Transaction& t) {
        auto sender = findUserByPk(us, t.getSender());
        (*sender).setBalance((*sender).getBalance() - t.getAmount());
        auto address = findUserByPk(us, t.getAddress());
        (*address).setBalance((*address).getBalance() + t.getAmount());
    }

  public:
    /**
     * @brief Adds new users
     *
     * @param count how many users to add
     * @param min the least number of coins a newly generated user can have
     * @param max the most number of coins a newly generated user can have
     */
    void generateUsers(const int& count, const int& min, const int& max) {
        for (int i = 0; i < count; i++) {
            users.emplace_back("user" + std::to_string(i),
                               generateRandomNumber(min, max));
#ifdef BE_VERBOSE
            std::cout << users.at(i) << std::endl;
#endif
        }
    }

    /**
     * @brief Generate new transaction and put them in a pool
     *
     * @param count how many transactions to generate
     * @param min the least possible transaction amount
     * @param max the biggest transaction possible
     */
    void generateTransactions(const int& count, const int& min, const int& max);

    /**
     * @brief The main function of this class. Mines the block. Pool needs
     * to have transactions and users vector needs to be populated in order
     * for this function to work.
     *
     */
    void mineBlock();

    friend std::ostream& operator<<(std::ostream& os, const Blockchain& b) {
        for (const auto& block : b.blockchain)
            os << block << std::endl;
        return os;
    }

    /**
     * @brief Checks if pool is empty
     *
     * @return true if empty, false if there are transactions in the pool
     */
    bool getPoolStatus() {
        return pool.empty();
    }

    const std::vector<User>& getUsers() {
        return users;
    }
};
