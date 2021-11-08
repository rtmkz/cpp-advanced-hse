#!/usr/bin/python3
import json
import sys

def get_benchmarks(filename):
    return json.load(open(filename))['benchmarks']

def get_score(results, baseline):
    for result, reference in zip(results, baseline):
        if result['real_time'] > 1500 or result['cpu_time'] > 5000:
            sys.exit(1)

if __name__ == '__main__':
    get_score(get_benchmarks(sys.argv[1]), get_benchmarks(sys.argv[2]))
