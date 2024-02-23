#!/bin/bash

gcc ./src/main/main.c -o ./build/Linux.out
./build/Linux.out "$1"