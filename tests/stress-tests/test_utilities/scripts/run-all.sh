#!/usr/bin/env bash
DIR=${1:-.}
# use a precompiled header for the template to improve perf
echo "start of compiling header"
g++ $(cat $(dirname "$0")/compile_flags.txt) $DIR/../template.h
echo "done compiling header"
trap "rm -f $DIR/../template.h.gch" EXIT
if [[ $# -eq 1 ]] ; then
    tests="$(find $DIR -name '*.cpp')"
else
    tests="$(find $DIR -name "*$2*")"
fi
echo "testing the following:" $tests
declare -i pass=0
declare -i fail=0
failTests=""
for test in $tests; do
    echo "$(basename $test): "
    start=`date +%s.%N`
    echo "start compiling test"
    g++ $(cat $(dirname "$0")/compile_flags.txt) $test
    echo "done compiling test"
    ./a.out
    echo "done running test"
    retCode=$?
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
    rm -f a.out
    echo
done
echo "$pass/$(($pass+$fail)) tests passed"
if (($fail == 0)); then
    echo "No tests failed"
    exit 0
else
    echo -e "These tests failed: \n $failTests"
    exit 1
fi
