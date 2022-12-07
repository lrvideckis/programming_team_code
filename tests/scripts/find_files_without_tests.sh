#!/usr/bin/env bash

git submodule init
git submodule update

echo ".hpp files included by no .test.cpp file:"
comm -23 <(
	find ../library/ -type f -name "*.hpp" |
		xargs basename --multiple |
		sort |
		uniq
) <(
	find online_judge_tests/ -type f -name "*.test.cpp" |
		xargs g++ -MM |
		xargs basename --multiple |
		grep "\.hpp$" |
		sort |
		uniq
)
