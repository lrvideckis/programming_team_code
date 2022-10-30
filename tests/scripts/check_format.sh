#! /bin/bash

#check snake case && astyle *before* initializing git submodules to avoid warnings not in our code
echo "check files and directories are snake_case:"
find ../library/ online_judge_tests/ -name "*[A-Z]*" -or -name "*-*" | \
	grep --invert-match ".verify-helper" | \
	grep --invert-match "README" && exit 1

(
	astyle --options=.astylerc --recursive "online_judge_tests/*.test.cpp"
	astyle --options=.astylerc --recursive "../library/*.hpp"
) | grep "Formatted" && exit 1

echo "check template<typename T> over template<class T>:"
grep --recursive --extended-regexp "template\s?<class" ../library/ && exit 1
echo "check formatting of template <typename T>:"
grep --recursive --extended-regexp "template<typename" ../library/ && exit 1

git submodule init
git submodule update

cppcheck --enable=all --inconclusive --suppressions-list=.cppcheck_suppression_list \
	--force --language=c++ --error-exitcode=1 --std=c++17 --max-ctu-depth=50 \
	$(find online_judge_tests/ -type f -name "*.test.cpp" && find ../library/ -type f -name "*.hpp") \
	|| exit 1

./scripts/tests_by_git_modification.sh | \
	awk '{print $NF}' | \
	parallel clang-tidy {} -- -std=c++17
