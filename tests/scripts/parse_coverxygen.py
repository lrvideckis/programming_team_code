#!/usr/bin/env python
import sys, json;
data = json.load(sys.stdin)
data = data["total"]
assert(data["documented_symbol_count"] == data["symbol_count"])
