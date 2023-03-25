#!/usr/bin/env bash
set -euo pipefail

git submodule init
git submodule update

find online_judge_tests/ -type f -name "*.test.cpp" |
	parallel clang-tidy --config-file=.config/.clang-tidy {} -- -std=c++17 ||
	exit 1
