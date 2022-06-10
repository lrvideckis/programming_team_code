#!/usr/bin/env bash

tests="$(find ../library -name "*.h")"

# temporarily grant executable permissions
chmod +x scripts/hash.sh

for test in $tests; do
	hash=$(cat $test | scripts/hash.sh)
	comment="cat $(eval basename $test) | ./hash.sh"
	sed --in-place "1s;^;//$comment\n//$hash\n;" $test
done

chmod -x scripts/hash.sh
