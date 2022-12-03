#!/usr/bin/env bash
#

#find dependencies of each test file (concatenate results)
all_test_dependencies=$(
	for file in $(find online_judge_tests/ -type f -name "*.test.cpp")
	do
		g++ -MM $file
	done
)
all_test_dependencies=$(
	for dependency in $all_test_dependencies
	do
		echo $(basename $dependency)
	done | grep --fixed-strings ".hpp" | sort | uniq
)

#find all headers in library/
all_headers=$(find ../library/ -type f -name "*.hpp")
all_headers=$(
	for header in $all_headers
	do
		echo $(basename $header)
	done | sort | uniq
)

#compare list with all headers in library/
echo "files with no tests:"
comm -23 <(tr ' ' '\n' <<< "$all_headers") <(tr ' ' '\n' <<< "$all_test_dependencies")
