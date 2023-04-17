#!/bin/bash
# http://redsymbol.net/articles/unofficial-bash-strict-mode/
set -euo pipefail

#adds hash code comments
for header in ../library/**/*.hpp; do
	hash=$(../library/contest/hash.sh <"$header")
	comment="cat $(basename "$header") | ./hash.sh"
	sed --in-place "1s;^;//$comment\n//$hash\n;" "$header"
done

# TODO replace underscores with spaces in file/directory names

git submodule init
git submodule update

(
	cd ../notebook-generator/
	npm ci
	npm run test
)
#testing that I'm still in the test folder
ls

./../notebook-generator/bin/notebookgen ../library/ --author "SDSM&T" --initials SDSM&T --output ./hackpack.pdf --size 8 --columns 3

# TODO replace spaces with underscores in file/directory names

#remove hash code comments
sed -i '1,2d' ../library/**/*.hpp
