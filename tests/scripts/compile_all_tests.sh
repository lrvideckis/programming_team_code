#!/usr/bin/env bash

git submodule init
git submodule update

scripts/add_symlink.sh

#compile code
declare -i pass=0
declare -i fail=0
fail_tests=""

scripts/tests_by_git_modification.sh | while read test
do
	#can't compile 2 files with main at the same time, so we need to compile each test separately
	echo "compiling "$test
	g++ $(echo $test | awk '{print $NF}') $(cat scripts/compile_flags.txt)
	if (($? != 0))
	then
		fail+=1
		fail_tests="$fail_tests$test_name\n"
	else
		pass+=1
	fi
done

echo "$pass/$(($pass+$fail)) tests passed"
if (($fail == 0)); then
	echo "No tests failed"
	exit 0
else
	echo -e "These tests failed: \n $fail_tests"
	exit 1
fi
