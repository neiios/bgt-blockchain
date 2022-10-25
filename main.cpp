#include <hash.hpp>
#include <iostream>
#include <vector>
#include "block.hpp"
#include "transaction.hpp"
#include "user.hpp"

using namespace std;

int main() {
    Hash h;
    cout << "Blockchain!\n";
    cout << h.hashString("Blockchain!") << endl;

    User u("user1", 100);
    cout << u << endl;

    Transaction t(h.hashString("user1"), h.hashString("user2"), 100);
    cout << t << endl;

    vector<Transaction> vt;
    vt.push_back(t);
    Block b("", 3, 1, vt);
    cout << b << endl;

    return 0;
}
