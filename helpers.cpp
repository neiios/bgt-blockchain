#include "helpers.hpp"

std::random_device dev;
std::mt19937 rng(dev());

int generateRandomNumber(const int& start, const int& end) {
    std::uniform_int_distribution<std::mt19937::result_type> dist(start, end);
    return dist(rng);
}

std::vector<User>::iterator findUser(std::vector<User>& users,
                                     const std::string& pk) {
    return std::find_if(users.begin(), users.end(),
                        [&pk](User u) { return u.getPublicKey() == pk; });
}

void updateUserBalance(const Transaction& transaction,
                       std::vector<User>& users) {
    auto sender = findUser(users, transaction.getSender());
    (*sender).setBalance((*sender).getBalance() - transaction.getAmount());
    auto address = findUser(users, transaction.getAddress());
    (*address).setBalance((*address).getBalance() + transaction.getAmount());
}
