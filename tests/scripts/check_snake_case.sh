#!/usr/bin/env bash

cd ..

files_snake_case="find . -name '*[A-Z]*' -or -name '*-*' | \
	grep --invert-match '\.git' | \
	grep --invert-match '\.verify-helper' | \
	grep --invert-match --extended-regexp '(LICENSE|Makefile|README)'"

if eval $files_snake_case --quiet
then
	echo "these files/directories are not snake case:"
	eval $files_snake_case
	exit 1
fi

cd library

declare -i pass=0
declare -i fail=0
failTests=""

echo "skipped headers: "
find . -name '*.h' | grep -Ff ../tests/scripts/skip_headers.txt

for test in $(find . -name '*.h' | grep -vFf ../tests/scripts/skip_headers.txt)
do
	echo "file is "$test

	tmp_file=$(dirname $test)"/tmp.cpp"

	cp ../template.cpp $tmp_file
	sed --regexp-extended '/^#pragma once/d' $test >> $tmp_file

	# clang's "lower_case" == the traditional snake_case
	clang-tidy -checks="readability-identifier-naming" \
		-config="{CheckOptions: [
			{ key: readability-identifier-naming.StructCase, value: lower_case },
			{ key: readability-identifier-naming.ClassCase, value: lower_case },
			{ key: readability-identifier-naming.FunctionCase, value: lower_case },
			{ key: readability-identifier-naming.MethodCase, value: lower_case },
			{ key: readability-identifier-naming.VariableCase, value: lower_case },
			{ key: readability-identifier-naming.ConstantCase, value: UPPER_CASE },
			{ key: readability-identifier-naming.ParameterCase, value: lower_case },
			{ key: readability-identifier-naming.TypedefCase, value: lower_case },
			{ key: readability-identifier-naming.TemplateParameterCase, value: UPPER_CASE }
		]}" \
		--use-color --warnings-as-errors="*" $tmp_file -- -std=c++17
	if (($? != 0))
	then
		fail+=1
		failTests="$failTests$test\n"
	else
		pass+=1
	fi
done

echo "$pass/$(($pass+$fail)) tests passed"
if (($fail == 0)); then
	echo "No tests failed"
	exit 0
else
	echo -e "These tests failed: \n $failTests"
	exit 1
fi
