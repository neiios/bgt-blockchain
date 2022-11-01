#pragma once
#include <chrono>
#include <cstdint>
#include <functional>
#include <hash.hpp>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include "defines.hpp"

class Transaction {
  private:
    // hash of other values
    std::string id;
    // public key of sender
    std::string sender;
    // public key of the user who gets the transaction
    std::string address;
    uint64_t timestamp;
    int amount;

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

    auto getSender() const { return sender; }
    auto getAddress() const { return address; }
    auto getAmount() const { return amount; }
    auto getSender() { return sender; }
    auto getAddress() { return address; }
    auto getAmount() { return amount; }

    std::string stringifyTransaction() {
        std::stringstream os;
        os << id << '/' << sender << '/' << address << '/' << timestamp << '/'
           << amount;
        return os.str();
    }

    friend std::ostream& operator<<(std::ostream& os, const Transaction& t) {
        os << t.id << '/' << t.sender << '/' << t.address << '/' << t.timestamp
           << '/' << t.amount;
        return os;
    }
};
