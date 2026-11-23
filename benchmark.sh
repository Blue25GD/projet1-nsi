#!/bin/bash

if [[ "$1" != "-r" ]]; then
    printf "\033[0;33m[INFO] Building project...\033[0m\n"
    cmake --build build
fi

printf "\033[0;33m[INFO] Running write benchmark...\033[0m"
rm -rf database.txt
time ./build/projet1_nsi < write_test.txt > /dev/null

printf "\033[0;33m[INFO] Running read benchmark...\033[0m"
time ./build/projet1_nsi < read_test.txt > /dev/null
