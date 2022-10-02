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

./scripts/tests_by_git_modification.sh | \
	awk '{print $NF}' | \
	parallel --bar clang-tidy {} -- -std=c++17
