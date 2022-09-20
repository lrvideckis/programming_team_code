#!/usr/bin/env bash

git submodule init
git submodule update

source scripts/add_symlink.sh

#compile code
declare -i pass=0
declare -i fail=0
failTests=""
for test in $(find online_judge_tests/ -type f -name '*.test.cpp')
do
	echo "file is "$test
	#can't compile 2 files with main at the same time, so we need to compile each test separately
	g++ $test $(cat scripts/compile_flags.txt)
	if (($? != 0))
	then
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
