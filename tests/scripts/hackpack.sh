#!/bin/bash
# http://redsymbol.net/articles/unofficial-bash-strict-mode/
set -euo pipefail
# ** glob now searches any number of levels
shopt -s globstar

WORD_LENGTH_THRESHOLD=60
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

# underscores in file names look bad in hackpack, so this
# replaces all underscores with spaces
find ../library/ -depth -execdir rename 'y/_/ /' {} +

# regarding school branding: https://brand.sdsmt.edu/identity/our-name/
# in particular, no initials
# logo taken from https://brand.sdsmt.edu/identity/official-logos/
notebook-generator ../library/ --author "South Dakota Mines" --output ./hackpack.pdf --size 8 --columns 3 --image .config/SouthDakotaMinesLogo.png

find ../library/ -depth -execdir rename 'y/ /_/' {} +

#remove hash code comments
sed -i '1,2d' ../library/**/*.hpp
