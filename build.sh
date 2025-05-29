#!/bin/bash

mkdir -p build

g++ -std=c++17 \
    -Isrc -Imodel -Icommon \
    src/main.cpp \
    model/Galaxy.cpp model/Planet.cpp model/Model.cpp \
    common/Reader.cpp \
    -o build/Warhammer10k
