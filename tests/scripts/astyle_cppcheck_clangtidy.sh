#!/usr/bin/env bash
set -euo pipefail

# miscellaneous checks - done before initializing git submodules to avoid checking stuff not in our code

echo "check no endl"
grep "endl" --recursive online_judge_tests/ && exit 1

echo "check template<typename T> over template<class T>:"
grep --extended-regexp "template\s?<class" --recursive ../library/ && exit 1

echo "check formatting of template <typename T>:"
grep --extended-regexp "template<typename" --recursive ../library/ && exit 1

echo "check 1 instead of true"
grep --extended-regexp "true" --recursive ../library/ && exit 1

echo "check 0 instead of false"
grep --extended-regexp "false" --recursive ../library/ && exit 1

echo "check files and directories are snake_case:"
find ../library/ online_judge_tests/ -name "*[A-Z]*" -or -name "*-*" |
	grep --invert-match ".verify-helper" |
	grep --invert-match "README" &&
	exit 1

WORD_LENGTH_THRESHOLD=80
echo "The following words are > $WORD_LENGTH_THRESHOLD characters, and won't wrap in PDF:"
find ../library/ -type f -name "*.hpp" |
	xargs cat |
	tr '[:blank:]' '\n' |
	awk --assign=max_len=$WORD_LENGTH_THRESHOLD '{if(length>max_len)print$0}' |
	grep . &&
	exit 1

(
	astyle --options=.config/.astylerc --recursive "online_judge_tests/*.test.cpp"
	astyle --options=.config/.astylerc --recursive "../library/*.hpp"
) | grep "Formatted" && exit 1

git submodule init
git submodule update

cppcheck --enable=all --inconclusive --suppressions-list=.config/.cppcheck_suppression_list \
	--force --language=c++ --error-exitcode=1 --std=c++17 --max-ctu-depth=50 \
	$(find online_judge_tests/ -type f -name "*.test.cpp" && find ../library/ -type f -name "*.hpp") ||
	exit 1

find online_judge_tests/ -type f -name "*.test.cpp" |
	parallel clang-tidy --config-file=.config/.clang-tidy {} -- -std=c++17 ||
	exit 1
