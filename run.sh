#!/bin/bash

DEBUG="-g"
if [ "$1" == "debug" ]; then
    DEBUG="-DDEBUG -g -O0"
fi

g++ -std=c++17 $DEBUG \
    -Isrc -Imodel -Icommon -Iview -Icontroller \
    src/*.cpp model/*.cpp common/*.cpp controller/*.cpp view/*.cpp \
    $(fltk-config --cxxflags) $(fltk-config --ldflags) -lfltk_images \
    -o ./Warhammer10k