#!/usr/bin/python3

import json
import sys

def get_benchmarks(filename):
    return json.load(open(filename))['benchmarks']

def get_score(results, baseline):
    if results[0]["cpu_time"] > 50:
        sys.exit(1)

if __name__ == '__main__':
    get_score(get_benchmarks(sys.argv[1]), get_benchmarks(sys.argv[2]))
