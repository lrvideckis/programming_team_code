#!/usr/bin/env bash

DIR=${1:-.}

tests="$(find $DIR/../Library -name "*.h")"

for test in $tests; do
	hash=$(cat $test | ./$DIR/scripts/hash.sh)
	comment="cat $(eval basename $test) | ./hash.sh"
	sed -i "1s;^;//$comment\n//$hash\n;" $test
done
