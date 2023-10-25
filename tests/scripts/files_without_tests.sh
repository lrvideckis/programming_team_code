#!/bin/bash
# http://redsymbol.net/articles/unofficial-bash-strict-mode/
set -euo pipefail
# ** glob now searches any number of levels
shopt -s globstar

git submodule init
git submodule update

echo ".hpp files included by no .test.cpp file:"
comm -23 --check-order <(
	basename --multiple ../library/**/*.hpp |
		sort |
		uniq
) <(
	g++ -MM library_checker_aizu_tests/**/*.test.cpp |
		xargs basename --multiple |
		grep "\.hpp$" |
		sort |
		uniq
)
