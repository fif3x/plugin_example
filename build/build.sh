#!/bin/bash

cd ..
make main
make lt-plugin
mkdir -p bin
mv main bin
mv lt-plugin bin
make clean

./bin/main