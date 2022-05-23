#!/usr/bin/env bash
DIR=${1:-.}
echo $DIR

tests=$(find $DIR/../library-checker-tests -name '*.test.cpp')

declare -i pass=0
declare -i fail=0
failTests=""
for test in $tests; do
	echo "test is: "
    echo $test
    start=`date +%s.%N`

	#get URL of library checker problem
	which_lib_problem=$(grep "#define PROBLEM" $test | grep -o '".*"' | tr -d '"')
	echo "grep result is"
	echo $which_lib_problem

	#get list of .h files which this test tests
	dependencies="a-"$(basename $test | sed s/\.cpp/\.d/)
	compile_res=$(g++ -MMD $test)
	echo "compile res is"
	echo $(cat $dependencies)





	retCode=0

    if (($retCode != 0)); then
        echo "Failed with $retCode"
        fail+=1
        failTests="$failTests$test\n"
    else
        pass+=1
    fi
    end=`date +%s.%N`
    runtime=$( echo "$end - $start" | bc -l )
    echo "Took $runtime seconds"
done
echo "$pass/$(($pass+$fail)) tests passed"
if (($fail == 0)); then
    echo "No tests failed"
    exit 0
else
    echo -e "These tests failed: \n $failTests"
    exit 1
fi
