#!/bin/bash
# http://redsymbol.net/articles/unofficial-bash-strict-mode/
set -euo pipefail

cd ..

echo "total number of tests:"
find tests/library_checker_aizu_tests/ -type f -name "*.test.cpp" | wc --lines

echo "number of tests which have run:"
grep "test.cpp" .verify-helper/timestamps.remote.json | wc --lines

echo "tests which have *not* run:"
comm -23 --check-order <(
    find tests/library_checker_aizu_tests/ -type f -name "*.test.cpp" |
		sort |
		uniq
) <(
    grep --only-matching '".*test.cpp"' .verify-helper/timestamps.remote.json |
        tr -d '"' |
		sort |
		uniq
) |
	grep . &&
	exit 1
