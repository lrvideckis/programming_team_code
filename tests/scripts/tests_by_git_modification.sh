B#!/bin/bash

git submodule init
git submodule update

source scripts/add_symlink.sh

#get all test files
all_test_files=$(find online_judge_tests/ -type f -name "*.test.cpp")

for file in $all_test_files
do
	deps_with_update_time=$(
		for dependency in $(g++ -MM $file)
		do
			case $dependency in *.hpp|*.test.cpp)
				git log -n 1 --date=iso-local --format="%ad" $dependency
			esac
		done | sort | tail -1
	)
	echo "$deps_with_update_time $file"
done | sort --reverse
