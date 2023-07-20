#!/bin/bash
#runs 2 programs against each other on random inputs until they output different results
#source: https://github.com/Errichto/youtube/blob/master/testing/s.sh
#usage:
#	chmod +x test.sh
#	./test.sh

g++ -std=c++17 a.cpp -o a.out
g++ -std=c++17 b.cpp -o b.out
g++ -std=c++17 test.cpp -o test.out

while :; do
	echo "hi"
	./test.out >in
	diff --ignore-all-space <(./a.out <in) <(./b.out <in) || break
done
