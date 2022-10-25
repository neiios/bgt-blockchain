#pragma once
#include <cstdint>
#include <iostream>
#include <string>
#include "hash.hpp"

class User {
  private:
    uint64_t balance;
    std::string username;
    std::string pk;

  public:
    User(const std::string& n, const uint64_t& b) : balance(b), username(n) {
        Hash h;
        pk = h.hashString(username);
    };

    friend std::ostream& operator<<(std::ostream& os, const User& u) {
        os << u.username << '/' << u.pk << '/' << u.balance;
        return os;
    }

    void setBalance(const uint64_t& b) { balance = b; }
};
