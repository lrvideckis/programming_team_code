#!/bin/bash

ASTYLE_COMMAND="astyle --indent=tab --style=attach --remove-braces --align-reference=type --align-pointer=type --delete-empty-lines --attach-classes --pad-oper --pad-header --unpad-paren --close-templates --indent-col1-comments --suffix=none"

if ! grep --quiet "$ASTYLE_COMMAND" README.md
then
	echo "command doesn't match what's in README.md. Maybe you changed the README's asyle command."
	exit 1
fi

cd Library

declare -i pass=0
declare -i fail=0
failTests=""

for test in $(find . -name '*.h')
do
	echo "file is "$test
	cpp -fpreprocessed -P -C $test > tmp
	sed --in-place '1s;^;#pragma once;' tmp
	eval $(echo $ASTYLE_COMMAND) tmp
	diff $test tmp
	if (($? != 0))
	then
		diff $test tmp
		fail+=1
		failTests="$failTests$test\n"
	else
		pass+=1
	fi
done

echo "$pass/$(($pass+$fail)) tests passed"
if (($fail == 0)); then
	echo "No tests failed"
	exit 0
else
	echo -e "These tests failed: \n $failTests"
	exit 1
fi
