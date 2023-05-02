#!/bin/bash
#runs 2 programs against each other on random inputs until they output different results
#source: https://github.com/Errichto/youtube/blob/master/testing/s.sh
#usage: bash test.sh
for ((i = 1; ; ++i)); do
	echo $i
	./test.out > input
	diff -w <(./a.out < input) <(./brute.out < input) || break
done
