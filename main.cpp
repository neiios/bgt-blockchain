#include <iostream>
#include <list>
#include <random>
#include <string>
#include <vector>
#include "blockchain.hpp"
#include "defines.hpp"

using namespace std;

int main() {
    // create blockchain
    Blockchain b;
    // generate new users
#ifdef BE_VERBOSE
    std::cout << "Generating users..." << std::endl;
#endif
    b.generateUsers(5, 100, 1000);
    // generate new transactions
#ifdef BE_VERBOSE
    std::cout << "Generating transactions..." << std::endl;
#endif
    b.generateTransactions(20, 10, 100);
    // mine block
    // TODO: fix a crash when sender has not enough balance
#ifdef BE_VERBOSE
    std::cout << "Mining..." << std::endl;
#endif
    while (!b.getPoolStatus())
        b.mineBlock();

    cout << endl << b << endl;
    return 0;
}
