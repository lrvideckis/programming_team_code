#!/bin/bash

#get all test files
all_test_files=$(find online_judge_tests/ -type f -name "*.test.cpp")

for file in $all_test_files
do
	deps_with_update_time=$(
		for dependency in $(g++ -MM $file)
		do
			case $dependency in *.hpp|*.test.cpp)
				git log --max-count=1 --date=iso-local --format="%ad" $dependency
			esac
		done | sort | tail --lines=1
	)
	echo "$deps_with_update_time $file"
done | sort --reverse
