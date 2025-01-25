#!/bin/bash

cd ../src && g++ *.cpp -g -o main ../build/external/CLIlib/libCLIlib.a ../build/external/fmt/libfmt.a
