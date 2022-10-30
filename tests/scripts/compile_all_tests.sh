#! /bin/bash

git submodule init
git submodule update

./scripts/tests_by_git_modification.sh | \
	awk '{print $NF}' | \
	parallel --bar g++ {} $(cat scripts/compile_flags.txt)
