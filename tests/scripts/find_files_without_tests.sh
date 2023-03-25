#!/bin/bash
set -euo pipefail

git submodule init
git submodule update

echo ".hpp files included by no .test.cpp file:"
comm -23 --check-order <(
	find ../library/ -type f -name "*.hpp" -print0 |
		xargs basename --multiple |
		sort |
		uniq
) <(
	find online_judge_tests/ -type f -name "*.test.cpp" -print0 |
		xargs g++ -MM |
		xargs basename --multiple |
		grep "\.hpp$" |
		sort |
		uniq
)
