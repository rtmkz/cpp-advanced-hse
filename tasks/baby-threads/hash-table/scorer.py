#!/usr/bin/python3
import json
import sys

def get_benchmarks(filename):
    return json.load(open(filename))['benchmarks']

def get_score(results):
    for result in results:
        if result['run_type'] != 'iteration':
            continue
        if result['real_time'] > 1500 or result['cpu_time'] > 5000:
            sys.exit(1)

if __name__ == '__main__':
    get_score(get_benchmarks(sys.argv[1]))
