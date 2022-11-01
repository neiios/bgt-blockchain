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
    auto getId() const { return id; }
    auto getSender() { return sender; }
    auto getAddress() { return address; }
    auto getAmount() { return amount; }
    auto getId() { return id; }

    /**
     * @brief Output transaction in a nicely formatted way.
     *
     */
    friend std::ostream& operator<<(std::ostream& os, const Transaction& t) {
        os << "Hash: " << t.id << " Amount: " << t.amount << " " << t.sender
           << " -> " << t.address << " Timestamp: " << t.timestamp;
        return os;
    }

    friend bool operator==(const Transaction& rhs, const Transaction& lhs) {
        return rhs.getId() == lhs.getId();
    }
};
