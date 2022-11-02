#!/usr/bin/env python
import sys, json;
data = json.load(sys.stdin)
cnt_documented_files = data["total"]["documented_symbol_count"]
total_files = data["total"]["symbol_count"]
print("number of documented files: " + str(cnt_documented_files))
print("total files: " + str(total_files))
print("asserting these are equal")
print(".")
print(".")
print(".")
assert(cnt_documented_files == total_files)
