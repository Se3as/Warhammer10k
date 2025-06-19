#!/bin/bash


g++ -std=c++17 -g \
    -Isrc -Imodel -Icommon -Iview -Icontroller  \
    src/*.cpp model/*.cpp common/*.cpp controller/*.cpp view/*.cpp  \
    $(fltk-config --cxxflags) $(fltk-config --ldflags) -lfltk_images \
    -o ./Warhammer10k