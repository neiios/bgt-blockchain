# Blockchain

## Projekto struktūra

```
bgt-blockchain
├── LICENSE
├── Makefile
├── bgt-hash
│   ├── LICENSE
│   ├── Makefile
│   ├── README.md
│   ├── hash.cpp
│   ├── hash.hpp
│   └── main.cpp
├── block.hpp
├── helpers.cpp
├── helpers.hpp
├── main.cpp
├── transaction.hpp
└── user.hpp
```

## Projekto setup'as

```
# clone the repository
git clone https://github.com/richard96292/bgt-blockchain

# compile program with make (must be inside the root project folder)
make

# run the blockchain simulation
./bin
```

## Programos veikimas

1. Naujų user'ių generavimas (1000)
1. Naujų transakcijų generavimas (10000)
1. Transakcijų iš pool'o pasirinkimas ir kasimas
1. Naujas blokas įrašomas į grandinę
1. Žingsiai 3-5 kartojami, kol pool'e yra transakcijos
