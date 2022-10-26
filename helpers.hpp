#include <random>
#include <vector>
#include "block.hpp"
#include "transaction.hpp"
#include "user.hpp"

int generateRandomNumber(const int& start, const int& end);

std::vector<User>::iterator findUser(std::vector<User>& users,
                                     const std::string& pk);

void updateUserBalance(const Transaction& transaction,
                       std::vector<User>& users);
