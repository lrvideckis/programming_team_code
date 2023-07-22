#!/bin/bash
# http://redsymbol.net/articles/unofficial-bash-strict-mode/
set -euo pipefail
# ** glob now searches any number of levels
shopt -s globstar

grep --recursive --files-with-matches library/contest/random\.hpp library_checker_aizu_tests/ |
	grep --invert-match --fixed-strings --file=- ../.verify-helper/timestamps.remote.json
