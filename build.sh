#!/bin/bash

mkdir -p build

g++ -std=c++17 \
    -Isrc -Imodel \
    src/main.cpp \
    model/Galaxy.cpp model/Planet.cpp \
    -o build/Warhammer10k
