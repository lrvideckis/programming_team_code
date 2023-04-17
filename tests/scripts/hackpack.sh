#!/bin/bash
# http://redsymbol.net/articles/unofficial-bash-strict-mode/
set -euo pipefail

WORD_LENGTH_THRESHOLD=65
echo "The following words are > $WORD_LENGTH_THRESHOLD characters, and won't wrap in PDF:"
cat ../library/**/*.hpp |
	tr '[:blank:]' '\n' |
	awk --assign=max_len="$WORD_LENGTH_THRESHOLD" '{if(length>max_len)print$0}' |
	grep . &&
	exit 1

#adds hash code comments
for header in ../library/**/*.hpp; do
	hash=$(../library/contest/hash.sh <"$header")
	comment="cat $(basename "$header") | ./hash.sh"
	sed --in-place "1s;^;//$comment\n//$hash\n;" "$header"
done

git submodule init
git submodule update

(
	cd ../notebook-generator/
	npm ci
	npm run test
)

find ../library/ -depth -execdir rename 's/_/ /g' {} \;

./../notebook-generator/bin/notebookgen ../library/ --author "SDSMT" --initials SDSMT --output ./hackpack.pdf --size 8 --columns 3

find ../library/ -depth -execdir rename 's/ /_/g' {} \;

#remove hash code comments
sed -i '1,2d' ../library/**/*.hpp
