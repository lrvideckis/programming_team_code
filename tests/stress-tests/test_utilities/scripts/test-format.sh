#!/bin/bash

cd Library

VAR=$(astyle --recursive "*.h" --indent=tab --remove-braces --style=attach --align-reference=type --align-pointer=type --delete-empty-lines --attach-classes --pad-oper --pad-header --unpad-paren --close-templates --dry-run --formatted | grep Formatted)

if [ -z "$VAR" ];
then
    echo "all code is formatted"
	exit 0
else
	echo "these files are not formatted:"
	echo "$VAR"
	exit 1
fi
