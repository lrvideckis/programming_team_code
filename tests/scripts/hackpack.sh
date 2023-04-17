#!/bin/bash
# http://redsymbol.net/articles/unofficial-bash-strict-mode/
set -euo pipefail

#adds hash code comments
for header in ../library/**/*.hpp; do
	hash=$(../library/contest/hash.sh <"$header")
	comment="cat $(basename "$header") | ./hash.sh"
	sed --in-place "1s;^;//$comment\n//$hash\n;" "$header"
done

# replace underscores with spaces in file/directory names

# run notebook-generator command

# replace spaces with underscores in file/directory names

#remove hash code comments
sed -i '1,2d' ../library/**/*.hpp
