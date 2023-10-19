#!/bin/bash
#Hashes a file, ignoring all:
#	- whitespace
#	- comments
#	- includes
#	- pragmas
#Use to verify that code was correctly typed.

#usage:
#	chmod +x hash.sh
#	cat a.cpp | ./hash.sh
#or just copy this command:
#	cat a.cpp | sed -r '/(include|pragma)/d' | cpp -dD -fpreprocessed -P | tr -d '[:space:]' | md5sum
sed -r '/(include|pragma)/d' | cpp -dD -fpreprocessed -P | tr -d '[:space:]' | md5sum
