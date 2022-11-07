# Blockchain

# v0.3 pakeitimai

Vietoj mano merkle tree realizacijos buvo panaudota create_merkle() funkciją.
Dabar, prieš kompiliuojant programą, reikės įsidiegti [libbitcoin-system v2](https://github.com/libbitcoin/libbitcoin-system/tree/v2.12.0) biblioteką.
Visus kodo pakeitimus galima peržiūrėti čia: https://github.com/richard96292/bgt-blockchain/commit/7f628822976fae5febfc646cc709173a5f5d7b32

## Projekto struktūra

```
bgt-blockchain
├── LICENSE
├── Makefile
├── README.md
├── bgt-hash
│   ├── LICENSE
│   ├── hash.cpp
│   └── hash.hpp
├── block.hpp
├── blockchain.cpp
├── blockchain.hpp
├── defines.hpp
├── helpers.cpp
├── helpers.hpp
├── main.cpp
├── merkleTree.hpp
├── script.sh
├── transaction.hpp
└── user.hpp

1 directory, 17 files
```

## Programos veikimas

1. Naujų user'ių generavimas (1000)
1. Naujų transakcijų generavimas (10000)
1. Transakcijų tikrinimas
1. Miner'ių kūrimas (lygiagrečiai)
1. Transakcijų iš pool'o pasirinkimas ir kasimas (lygiagrečiai)
1. Bloko tikrinimas
1. Naujas blokas įrašomas į grandinę
1. Žingsiai 3-5 kartojami, kol pool'e yra transakcijos

## Projekto setup'as

```
# clone the repository
git clone https://github.com/richard96292/bgt-blockchain

# install libbitcoin library

# compile program with make (must be inside the root project folder)
make

# run the blockchain simulation
./bin -b
```
