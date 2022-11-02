#include <getopt.h>
#include <omp.h>
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

std::string printLines() {
    std::stringstream os;
#ifdef BE_VERBOSE
    os << std::string(50, '-') << std::endl;
#endif
    return os.str();
}

void simulateBlockchain() {
    // create blockchain
    Blockchain b;
    // generate new users
    std::cout << printLines() << "Generating users..." << std::endl
              << printLines();
    b.generateUsers(USER_COUNT, MIN_BALANCE, MAX_BALANCE);
    // generate new transactions
    std::cout << printLines() << "Generating transactions..." << std::endl
              << printLines();
    b.generateTransactions(TRANSACTION_COUNT, MIN_TRANSACTION, MAX_TRANSACTION);
    // verify transactions
    b.verifyTransactions();
    // mine the block
    std::cout << printLines() << "Mining..." << std::endl;
    do {
        std::cout << "Started mining block " << b.getBlocks().size()
                  << std::endl;
        bool finishedMining = false;
        // parallel mining
#pragma omp parallel for num_threads(MINER_COUNT) shared(finishedMining)
        for (int i = 0; i < MINER_COUNT; i++) {
            b.mineBlock(b.getBlocks().size(), finishedMining);
        }
    } while (!b.getPoolStatus());
    // more info at the end
    std::cout << printLines() << "Final state:\n"
              << std::string(50, '-') << b << std::endl;
    std::cout << printLines() << "User balance at the end:\n" << printLines();
    for (const User& user : b.getUsers()) {
        std::cout << user << endl;
    }
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
