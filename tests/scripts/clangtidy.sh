#!/bin/bash
# http://redsymbol.net/articles/unofficial-bash-strict-mode/
set -euo pipefail

git submodule init
git submodule update

find library_checker_aizu_tests/ -type f -name "*.test.cpp" |
	parallel clang-tidy --config-file=.config/.clang-tidy {} -- -std=c++17 ||
	exit 1
