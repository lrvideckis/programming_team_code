#!/usr/bin/env python
import sys, json;
data = json.load(sys.stdin)["kinds"]

print()
print("asserting all functions are documented")
assert(data["function"]["documented_symbol_count"] == data["function"]["symbol_count"])

print("asserting all structs are documented")
assert(data["struct"]["documented_symbol_count"] == data["struct"]["symbol_count"])
