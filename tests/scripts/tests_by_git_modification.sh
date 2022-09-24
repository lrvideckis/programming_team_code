#! /bin/bash

#get all test (*.test.cpp) files, ordered by most recently modified

for file in $(find online_judge_tests/ -type f -name "*.test.cpp")
do
	# find the latest commit touching any dependency
	deps_with_update_time=$(
		for dependency in $(g++ -MM $file)
		do
			case $dependency in *.hpp|*.test.cpp)
				git log --max-count=1 --date=iso-local --format="%ad" $dependency
			esac
		done | sort | tail --lines=1
	)
	# output commit time concatenated with test file name
	echo "$deps_with_update_time $file"
done | sort --reverse
