#!/bin/bash
# ** glob now searches any number of levels
shopt -s globstar

grep --recursive --files-with-matches \
	-e "library/contest/random\.hpp" \
	-e "https\://judge\.yosupo\.jp/problem/" library_checker_aizu_tests/ |
	grep --invert-match --fixed-strings --file=- ../.verify-helper/timestamps.remote.json >tmp_file

mv tmp_file ../.verify-helper/timestamps.remote.json

# remove trailing new line. If you don't do this, the `oj-verify run` won't
# read this file correctly, and rerun all tests.
truncate --size=-1 ../.verify-helper/timestamps.remote.json
