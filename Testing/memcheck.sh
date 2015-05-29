#!/bin/sh

echo "-- MODULE MATRIX --"
valgrind -q ./bin/TestMatrix

echo "-- MODULE GRAPH --"
valgrind -q ./bin/TestGraph

echo "-- MODULE MST --"
valgrind -q ./bin/TestMST

echo "-- MODULE BRUTEFORCE --"
valgrind -q ./bin/TestBruteforce

echo "-- MODULE NN --"
valgrind -q ./bin/TestNearestNeighbour

echo "-- MODULE BRANCHANDBOUND --"
valgrind -q ./bin/TestBranchAndBound

echo "-- MODULE TSP --"
valgrind -q ./bin/TestTSP
