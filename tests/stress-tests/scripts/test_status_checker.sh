#!/usr/bin/env bash
DIR=${1:-.}
echo $DIR

tests=$(find $DIR/../library-checker-tests -name '*.test.cpp')

declare -i fail=0
failTests=""
for test in $tests
do
	echo "processing library checker test with file name = "$test

	#get URL of library checker problem
	which_lib_problem=$(grep "#define PROBLEM" $test | grep -o '".*"' | tr -d '"')

	#get list of .h files which this test tests
	g++ -std=c++17 -MMD $test
	dependencies=$(basename $test | sed s/\.cpp/\.d/)
	for dep in $(cat $dependencies | tr '\\' '\n')
	do
		if $(echo $dep | grep --quiet --extended-regexp "*\/Library\/*")
		then
			echo "testing dependency "$(basename $dep)" of "$(basename $test)
			if ! grep --quiet --extended-regexp "//library checker tests:.*$which_lib_problem.*" $dep
			then
				echo "Fail! no comment specifying file "$(basename $dep)" is tested on "$which_lib_problem
				echo "need to add comment which is picked up by the following command:"
				echo "grep --extended-regexp \"//library checker tests:.*$which_lib_problem.*\" $(basename $dep)"
				echo "Example comment format:"
				echo "//library checker tests: "$which_lib_problem
				fail=1
			fi
			echo "finished testing dependency "$(basename $dep)" of "$(basename $test)
			echo
		fi
	done
done

exit $fail
