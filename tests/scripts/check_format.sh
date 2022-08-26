#!/usr/bin/env bash

#check file names are snake case
files_snake_case="find .. -name '*[A-Z]*' -or -name '*-*' | \
	grep --invert-match '\.git' | \
	grep --invert-match '\.verify-helper' | \
	grep --invert-match 'ac-library' | \
	grep --invert-match '\.clang-tidy' | \
	grep --invert-match --extended-regexp '(LICENSE|Makefile|README)'"
if eval $files_snake_case --quiet
then
	echo "these files/directories are not snake case:"
	eval $files_snake_case
	exit 1
fi

#check files are formatted with astyle
ASTYLE_COMMAND="astyle --indent=tab --style=attach --remove-braces --align-reference=type --align-pointer=type --delete-empty-lines --attach-classes --pad-oper --pad-header --unpad-paren --close-templates --indent-col1-comments --suffix=none"
if ! grep --quiet "$ASTYLE_COMMAND" ../README.md
then
	echo "command doesn't match what's in README.md. Maybe you changed the README's asyle command."
	exit 1
fi
cd ..
astyle_output=$(
	$(echo $ASTYLE_COMMAND) --dry-run --formatted --recursive "*.test.cpp" &&
	$(echo $ASTYLE_COMMAND) --dry-run --formatted --recursive "*.h"
)
cd tests/
if grep --quiet "Formatted" <<< "$astyle_output"
then
	echo "some files are not formatted, output of astyle: "
	echo "$astyle_output"
	exit 1
fi

git submodule init
git submodule update

#check snake case
declare -i pass=0
declare -i fail=0
failTests=""
for test in $(find oj_tests/ -type f -name '*.test.cpp')
do
	echo "file is "$test
	g++ $test $(cat scripts/compile_flags.txt) && clang-tidy $test -- -std=c++17
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
