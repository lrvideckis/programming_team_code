#!/usr/bin/env bash
#Hashes a file, ignoring all:
#	- whitespace
#	- comments
#	- asserts
#	- includes
#	- pragmas
#Use to verify that code was correctly typed.

#usage:
#	chmod +x hash.sh
#	cat <file> | ./hash.sh
#or just copy this command:
#	cat <file> | sed -r '/(assert|include|pragma)/d' | cpp -fpreprocessed -P | tr -d '[:space:]' | md5sum | cut -c-6
sed -r '/(assert|include|pragma)/d' | cpp -fpreprocessed -P | tr -d '[:space:]' | md5sum | cut -c-6
