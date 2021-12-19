#!/usr/bin/env bash
DIR=${1:-.}

# use a precompiled header for the template to improve perf
g++ -Wall -Wextra -pedantic -Wno-unused-result -Wfatal-errors -DLOCAL -std=c++2a -O2 -Wshadow -Wformat=2 -Wfloat-equal -Wcast-qual -Wcast-align -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all -fstack-protector -x c++-header $DIR/template.cpp
trap "rm -f $DIR/template.cpp.gch" EXIT

SCRIPT_DIR=$DIR/scripts
tests="$(find $DIR/content -name '*.h')"
declare -i pass=0
declare -i fail=0
failHeaders=""
for test in $tests; do
    echo "$(basename $test): "
    $SCRIPT_DIR/test-compiles.sh $test
    retCode=$?
    if (($retCode != 0)); then
        echo $retCode
        fail+=1
        failHeaders="$failHeaders$test\n"
    else
        pass+=1
    fi
    echo
done
echo "$pass/$(($pass+$fail)) tests passed"
if (($pass == 0)); then
    echo "No tests found"
    exit 1
elif (($fail == 0)); then
    echo "No tests failed"
    exit 0
else
    echo -e "These tests failed: \n $failHeaders"
    exit 1
fi
