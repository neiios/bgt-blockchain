#include <getopt.h>
#include <iostream>
#include <list>
#include <random>
#include <string>
#include <vector>
#include "blockchain.hpp"
#include "defines.hpp"

using namespace std;

string outputHelp() {
    stringstream res;
    res << "pass -b to simulate a blockchain\n"
        << "pass -s to hash a string\n";
    return res.str();
}

void simulateBlockchain() {
    // create blockchain
    Blockchain b;
    // generate new users
#ifdef BE_VERBOSE
    std::cout << "Generating users..." << std::endl;
#endif
    b.generateUsers(USER_COUNT, MIN_BALANCE, MAX_BALANCE);
    // generate new transactions
#ifdef BE_VERBOSE
    std::cout << "Generating transactions..." << std::endl;
#endif
    b.generateTransactions(TRANSACTION_COUNT, MIN_TRANSACTION, MAX_TRANSACTION);
    // mine block
    // TODO: fix a crash when sender has not enough balance
#ifdef BE_VERBOSE
    std::cout << "Mining..." << std::endl;
#endif
    while (!b.getPoolStatus()) {
        b.mineBlock();
        cout << endl << b << endl;
    }

#ifdef BE_VERBOSE
    std::cout << "User balance at the end:" << std::endl;
    for (const User& user : b.getUsers()) {
        std::cout << user << endl;
    }
#endif
}

int main(int argc, char* argv[]) {
    int c, index;
    Hash h;

    if (argc == 1) {
        cout << outputHelp();
        return 42;
    }

    while ((c = getopt(argc, argv, "bs:h")) != -1) {
        switch (c) {
            case 'b':
                simulateBlockchain();
                break;
            case 's':
                cout << h.hashString(optarg) << endl;
                break;
            case 'h':
                cout << outputHelp();
                break;
            case '?':
                return 42;
            default:
                abort();
        }
    }

    for (index = optind; index < argc; index++)
        printf("Non-option argument %s\n", argv[index]);

    return 0;
}
