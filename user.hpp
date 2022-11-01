#pragma once
#include <cstdint>
#include <iostream>
#include <string>
#include "hash.hpp"

class User {
  private:
    int balance;
    std::string username;
    std::string sk;
    std::string pk;

  public:
    User(const std::string& n, const uint64_t& b) : balance(b), username(n) {
        Hash h;
        sk = h.hashString(username);
        pk = h.hashString(sk);
    };

    /**
     * @brief Output the data in a nicely formatted way.
     *
     */
    friend std::ostream& operator<<(std::ostream& os, const User& u) {
        os << "Username: " << u.username << " Balance: " << u.balance
           << " Public key: " << u.pk;
        return os;
    }

    void setBalance(const uint64_t& b) { balance = b; }
    auto getBalance() { return balance; }
    auto getBalance() const { return balance; }

    std::string getPublicKey() { return pk; }
    std::string getUsername() { return username; }
};
