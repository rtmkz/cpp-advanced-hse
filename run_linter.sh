#!/bin/bash

# Run from build directory

if [ "$#" -lt 1 ]; then
    echo "Usage: $0 task-name"
    exit 1
fi

TASK_PATH=../tasks/$1
CLANG_PATH=../run-clang-format.py
CLANG_TIDY=clang-tidy-11

if [ ! -f compile_commands.json ]; then
    echo "Run this script from the build directory"
    exit 1
fi

if [ "$#" -eq 2 ]; then
    TASK_PATH=../../tasks/$1
    CLANG_PATH=../../run-clang-format.py
    CLANG_TIDY="hse-clang-tidy --extra-arg=-I/usr/lib/clang/11/include/"
fi

if [ "$#" -eq 3 ]; then
    $CLANG_TIDY --config=$3 $TASK_PATH/*.cpp
fi

$CLANG_PATH -r $TASK_PATH
$CLANG_TIDY $TASK_PATH/*.cpp
