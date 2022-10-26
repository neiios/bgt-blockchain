#include <random>
#include <vector>
#include "block.hpp"
#include "user.hpp"

int generateRandomNumber(const int& start, const int& end);

std::vector<User>::iterator findUser(std::vector<User>& users,
                                     const std::string& pk);

void updateUserBalance(const Block& newBlock, std::vector<User>& users);
