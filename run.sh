#!/bin/bash

mkdir -p build

g++ -std=c++17 -g \
    -Isrc -Imodel -Icommon \
    src/*.cpp model/*.cpp common/*.cpp \
    -o build/Warhammer10k