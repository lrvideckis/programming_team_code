#!/bin/bash
# http://redsymbol.net/articles/unofficial-bash-strict-mode/
set -euo pipefail
# ** glob now searches any number of levels
shopt -s globstar

grep --recursive --files-with-matches \
	-e "library/contest/random\.hpp" \
	-e "https\://judge\.yosupo\.jp/problem/" library_checker_aizu_tests/ |
	grep --invert-match --fixed-strings --file=- ../.verify-helper/timestamps.remote.json >tmp_file

mv tmp_file ../.verify-helper/timestamps.remote.json

git add ../.verify-helper/timestamps.remote.json
git commit --message "removing randomly generated tests to rerun them"
git push
