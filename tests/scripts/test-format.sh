#!/bin/bash

ASTYLE_COMMAND="astyle --indent=tab --style=attach --remove-braces --align-reference=type --align-pointer=type --delete-empty-lines --attach-classes --pad-oper --pad-header --unpad-paren --close-templates --indent-col1-comments --recursive \"\*.h\" --suffix=none"

if ! grep --quiet "$ASTYLE_COMMAND" README.md
then
	echo "command doesn't match what's in README.md. Maybe you changed the README's asyle command."
	exit 1
fi

cd Library

VAR=$(eval $(echo $ASTYLE_COMMAND | tr -d "\\") --dry-run --formatted | grep Formatted)

if [ -z "$VAR" ];
then
    echo "all code is formatted"
	exit 0
else
	echo "these files are not formatted:"
	echo "$VAR"
	exit 1
fi
