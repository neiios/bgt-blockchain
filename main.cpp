#include <hash.hpp>
#include <iostream>

using namespace std;

int main() {
  Hash h;
  cout << "Blockchain!\n";
  cout << h.hashString("Blockchain!") << endl;
  return 0;
}
