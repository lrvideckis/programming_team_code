#!/usr/bin/env bash

git submodule init
git submodule update

find online_judge_tests/ -type f -name "*.test.cpp" |
	parallel g++ {} $(cat .config/.gcc_compile_flags)
