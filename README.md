# Blockchain

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

## Projekto setup'as

```
# clone the repository
git clone https://github.com/richard96292/bgt-blockchain

# compile program with make (must be inside the root project folder)
make

# run the blockchain simulation
./bin -b
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
