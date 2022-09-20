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
	$ASTYLE_COMMAND --dry-run --formatted --recursive "*.test.cpp" &&
	$ASTYLE_COMMAND --dry-run --formatted --recursive "*.hpp"
)
cd tests/
if grep --quiet "Formatted" <<< "$astyle_output"
then
	echo "some files are not formatted, output of astyle: "
	echo "$astyle_output"
	exit 1
fi

#run cppcheck formatter before initializing git submodules to avoid warnings not in our code
cppcheck online_judge_tests/ --file-filter="*.test.cpp" --enable=all --suppress=noExplicitConstructor --suppress=assertWithSideEffect --inconclusive --error-exitcode=1 --std=c++17 --max-ctu-depth=50
if (($? != 0))
then
	echo "cppcheck failed"
	exit 1
fi

git submodule init
git submodule update

scripts/add_symlink.sh

#lint code
declare -i pass=0
declare -i fail=0
fail_tests=""

scripts/tests_by_git_modification.sh | while read test
do
	# run clang tidy one-by-one to get quicker output
	# also running clang-tidy on all tests in a single command gives no speed-up
	echo
	echo "running clang-tidy on "$test
	clang-tidy $(echo $test | awk '{print $NF}') -- -std=c++17
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
