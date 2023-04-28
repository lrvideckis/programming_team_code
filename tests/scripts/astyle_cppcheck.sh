#!/bin/bash
# http://redsymbol.net/articles/unofficial-bash-strict-mode/
set -euo pipefail
# ** glob now searches any number of levels
shopt -s globstar

# miscellaneous checks - done before initializing git submodules to avoid checking stuff not in our code

echo "check no endl"
grep "endl" --recursive library_checker_aizu_tests/ && exit 1

echo "check template<typename T> over template<class T>:"
grep --extended-regexp "template\s?<class" --recursive ../library/ && exit 1

echo "check formatting of template <typename T>:"
grep --extended-regexp "template<typename" --recursive ../library/ && exit 1

echo "check 1 instead of true"
grep --extended-regexp "true" --recursive ../library/ && exit 1

echo "check 0 instead of false"
grep --extended-regexp "false" --recursive ../library/ && exit 1

echo "check files and directories are snake_case:"
find ../library/ library_checker_aizu_tests/ -name "*[A-Z]*" -or -name "*-*" |
	grep --invert-match ".verify-helper" |
	grep --invert-match "README" &&
	exit 1

echo ".hpp files missing pragma once:"
comm -23 --check-order <(
	find ../library/ -type f -name "*.hpp" |
		sort |
		uniq
) <(
	grep --fixed-strings "#pragma once" --recursive ../library/ --files-with-matches |
		sort |
		uniq
) |
	grep . &&
	exit 1

astyle --options=.config/.astylerc --recursive "library_checker_aizu_tests/*.test.cpp" "../library/*.hpp" |
	grep "Formatted" && exit 1

git submodule init
git submodule update

cppcheck --enable=all --inconclusive --suppressions-list=.config/.cppcheck_suppression_list \
	--force --language=c++ --error-exitcode=1 --std=c++17 --max-ctu-depth=50 \
	../library/**/*.hpp library_checker_aizu_tests/**/*.test.cpp ||
	exit 1
