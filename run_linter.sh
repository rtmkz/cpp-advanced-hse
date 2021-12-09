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

if [ "$#" -ge 2 ]; then
    TASK_PATH=../../tasks/$1
    CLANG_PATH=../../run-clang-format.py
    CLANG_TIDY="hse-clang-tidy --extra-arg=-I/usr/lib/clang/11/include/"
fi


set -e
set -u
set -o pipefail
set -x

jq -r '.allow_change | if type=="array" then .[] else . end' --raw-output $TASK_PATH/.tester.json | sed "s|^|$TASK_PATH\/|g" | egrep '\.c$|\.cpp$|\.h$|\.hpp$' | xargs -I@ sh -c "ls @" | xargs $CLANG_PATH -r

if [ "$#" -eq 3 ]; then
    jq -r '.allow_change | if type=="array" then .[] else . end' --raw-output $TASK_PATH/.tester.json | sed "s|^|$TASK_PATH\/|g" | egrep '\.c$|\.cpp$|\.h$|\.hpp$' | xargs -I@ sh -c "ls @" | xargs -I@ sh -c "$CLANG_TIDY --config=$3 @"
fi

$CLANG_PATH -r $TASK_PATH
$CLANG_TIDY $TASK_PATH/*.cpp
