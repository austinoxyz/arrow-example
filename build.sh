#!/usr/bin/sh
g++ -Wall -Wextra -Werror -Wno-unused -o main main.cpp `pkg-config --cflags --libs raylib`
