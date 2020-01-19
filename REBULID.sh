#! /bin/bash

date
echo ""
echo "clean"
make clean
echo ""
echo "rebulid"
make
echo ""
echo "run"
./App/app