#!/bin/bash

git submodule init
git submodule update

source scripts/add_symlink.sh

#get all test files
all_test_files=$(find online_judge_tests/ -type f -name "*.test.cpp")

for file in $all_test_files
do
	echo "start of file"

	deps_by_git_log=$(
		for dependency in $(g++ -MM $file)
		do
		case $dependency in *.hpp|*.test.cpp)
			git log -n 1 --date=iso-local --format="%ad $dependency" $dependency
		esac
		done
	)

	echo $deps_by_git_log

	$deps_by_git_log | sort | tail -1
done
