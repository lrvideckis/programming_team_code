#!/bin/bash

#get all test files
all_test_files=$(find . -type f -name "*.test.cpp")

#find dependencies of each test file (concatenate results)
all_test_dependencies=$(for file in $all_test_files
do
	g++ -MM $file
done)
all_tested_headers=$(for dependency in $all_test_dependencies
do
	echo $(basename $dependency)
done | sort | uniq | grep "\.h")

#find all headers in library/
all_headers_raw=$(find ../library/ -type f -name "*.h")
all_headers_clean=$(for header in $all_headers_raw
do
	echo $(basename $header)
done | sort | uniq)

#compare list with all headers in library/
echo "files with no tests:"
comm -23 <(tr ' ' '\n' <<< "$all_headers_clean") <(tr ' ' '\n' <<< "$all_tested_headers")
