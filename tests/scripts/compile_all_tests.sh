#! /bin/bash

git submodule init
git submodule update

./scripts/tests_by_git_modification.sh | \
	awk '{print $NF}' | \
	parallel g++ {} $(cat .gcc_compile_flags)
