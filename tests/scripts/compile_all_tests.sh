#!/bin/bash
set -euo pipefail

git submodule init
git submodule update

find online_judge_tests/ -type f -name "*.test.cpp" |
	parallel g++ {} "$(tr '\n' ' ' <.config/.gcc_compile_flags)"
