#pragma once
#include <chrono>
#include <cstdint>
#include <functional>
#include <hash.hpp>
#include <iostream>
#include <string>

class Transaction {
  private:
    // hash of other values
    std::string id;
    // public key of sender
    std::string sender;
    // public key of the user who gets the transaction
    std::string address;
    uint64_t timestamp;
    uint64_t amount;

  public:
    Transaction(const std::string& s, const std::string& ad, const uint64_t& am)
        : sender(s),
          address(ad),
          timestamp(
              std::chrono::system_clock::now().time_since_epoch().count()),
          amount(am) {
        Hash h;
        id = h.hashString(sender + address + std::to_string(timestamp) +
                          std::to_string(amount));
    }

    friend std::ostream& operator<<(std::ostream& os, const Transaction& t) {
        os << t.id << '/' << t.sender << '/' << t.address << '/' << t.timestamp
           << '/' << t.amount;
        return os;
    }
};
