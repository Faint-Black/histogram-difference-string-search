#!/bin/sh

gcc histogram.c -o libhistogram.so \
    -ansi -pedantic -Wall -Wextra \
    -shared -fPIC -O3 -march=native
