#!/usr/bin/env bash
DIR=${1:-.}
echo $DIR

tests=$(find $DIR/ -name '*.cpp')

declare -i fail=0
for test in $tests
do
	echo "processing stress test with file name = "$test
	#get list of .h files which this test tests
	g++ -std=c++17 -MMD $test
	dependencies="a-"$(basename $test | sed s/\.cpp/\.d/)
	for dep in $(cat $dependencies | tr '\\' '\n')
	do
		if $(echo $dep | grep --quiet --extended-regexp "*\/Library\/*")
		then
			short_test=$(echo $test | cut --characters 3-)
			if ! grep --quiet --extended-regexp "//stress tests:.*tests/stress-tests/$short_test.*" $dep
			then
				echo "FAIL!!!!!!!!"
				echo "no comment specifying file "$(basename $dep)" is tested by "$test
				echo "need to add comment which is picked up by the following command:"
				echo "grep --quiet --extended-regexp \"//stress tests:.*tests/stress-tests/$short_test.*\" $(basename $dep)"
				echo "Example comment format:"
				echo "//stress tests: tests/stress-tests/"$short_test
				fail=1
			fi
		fi
	done
done

exit $fail
