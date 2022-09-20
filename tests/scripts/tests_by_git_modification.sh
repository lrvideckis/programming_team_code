#!/bin/bash

git submodule init
git submodule update

source scripts/add_symlink.sh

git log -n 10

#get all test files
all_test_files=$(find online_judge_tests/ -type f -name "*.test.cpp")

for file in $all_test_files
do
	echo "start of file"
	for dependency in $(g++ -MM $file)
	do
		case $dependency in *.hpp|*.test.cpp)
			git log -n 1 --date=iso-local --format="%ad $dependency" $dependency
		esac
	done | sort

	echo "middle of file"

	for dependency in $(g++ -MM $file)
	do
		case $dependency in *.hpp|*.test.cpp)
			#git log -n 1 --date=iso-local --format="%ad $dependency" $dependency
			git log $dependency
		esac
	done | sort | tail -1

	echo "end of file"
done
