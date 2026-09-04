#!/usr/bin/bash

cd Example/
make -i
make clean
cd ..

cd list-command-interpreter/
make -i
make clean
cd ..

cd kv-command-interpreter/
make -i
make clean
cd ..
