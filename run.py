#!/usr/bin/env python3

import subprocess
import sys

ind = 1

if len(sys.argv) >= 2 and sys.argv[1] == "c":
    subprocess.call("./compile.py")
    ind += 1

subprocess.call("./build/aoc/aoc " + ' '.join(sys.argv[ind:]), shell=True)
