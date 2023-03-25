#!/bin/bash
set -euo pipefail

git submodule init
git submodule update

echo ".hpp files included by no .test.cpp file:"
comm -23 --check-order <(
	basename --multiple ../library/**/*.hpp |
		sort |
		uniq
) <(
	g++ -MM online_judge_tests/**/*.test.cpp |
		xargs basename --multiple |
		grep "\.hpp$" |
		sort |
		uniq
)
