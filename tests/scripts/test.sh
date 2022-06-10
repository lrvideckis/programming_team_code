#!/usr/bin/env bash
#runs 2 programs against each other on random inputs until they output different results
#usage:
#	chmod +x test.sh
#	./test.sh
for((i = 1; ; ++i)); do
	echo $i
	./test.out > in
	diff --ignore-all-space <(./a.out < in) <(./brute.out < in) || break
done
