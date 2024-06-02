#!/bin/sh

set -xe

gcc -Wextra -Wall -o tetris src/*.c -Iraylib_5.0/include -Lraylib_5.0/lib -lraylib
./tetris