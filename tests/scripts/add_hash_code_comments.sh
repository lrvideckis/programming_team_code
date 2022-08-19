#!/usr/bin/env bash

tests="$(find ../library -name "*.h")"

for test in $tests; do
	hash=$(cat $test | scripts/hash.sh)
	comment="cat $(eval basename $test) | ./hash.sh"
	sed --in-place "1s;^;//$comment\n//$hash\n;" $test
done
