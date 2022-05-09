#!/bin/bash

ASTYLE_COMMAND=$(cat README.md | grep '^astyle*')

cd Library

VAR=$(eval $ASTYLE_COMMAND --dry-run --formatted | grep Formatted)

if [ -z "$VAR" ];
then
    echo "all code is formatted"
	exit 0
else
	echo "these files are not formatted:"
	echo "$VAR"
	exit 1
fi
