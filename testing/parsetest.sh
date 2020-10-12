#!/bin/bash

cd testing
cmake CMakeLists.txt
make && ./runTests
