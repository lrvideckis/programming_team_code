#! /bin/bash

echo "check files and directories are snake_case:"
find ../library/ online_judge_tests/ -name "*[A-Z]*" -or -name "*-*" | \
	grep --invert-match ".verify-helper" | \
	grep --invert-match "README" && exit 1

echo "run astyle on all files:"
astyle_output=$(
	astyle --options=.astylerc --recursive "online_judge_tests/*.test.cpp" && \
	astyle --options=.astylerc --recursive "../library/*.hpp"
)
echo "$astyle_output" | grep "Formatted" && exit 1

#run cppcheck formatter before initializing git submodules to avoid warnings not in our code
echo "run cppcheck on all files:"
cppcheck online_judge_tests/ --file-filter="*.test.cpp" --enable=all --suppress=noExplicitConstructor --suppress=assertWithSideEffect --inconclusive --error-exitcode=1 --std=c++17 --max-ctu-depth=50 || exit 1

git submodule init
git submodule update

./scripts/add_symlink.sh

#lint code
declare -i pass=0
declare -i fail=0
fail_tests=""

echo "run clang-tidy on all files:"
while read test
do
	# run clang tidy one-by-one to get quicker output
	# also running clang-tidy on all tests in a single command gives no speed-up
	echo "last modified date; file to run clang-tidy "$test
	if clang-tidy $(echo $test | awk '{print $NF}') -- -std=c++17
	then
		pass+=1
	else
		fail+=1
		fail_tests="$fail_tests$test\n"
	fi
done < <(./scripts/tests_by_git_modification.sh)

echo "$pass/$(($pass+$fail)) tests passed"
if (($fail == 0))
then
	echo "No tests failed"
	exit 0
else
	echo -e "These tests failed: \n $fail_tests"
	exit 1
fi
