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

# remove #pragma once
sed --in-place '/#pragma once/d' ../library/**/*.hpp
sed --in-place ';/** @file */;d' ../library/**/*.hpp

#adds hash code comments
for header in ../library/**/*.hpp; do
	hash=$(cat "$header" | sed '/#include/d' | cpp -dD -P -fpreprocessed | ../library/contest/hash.sh)
	sed --in-place "1i //hash: $hash" "$header"
done

git submodule init
git submodule update

# install dependencies listed in ../notebook-generator/package.json
npm ci --prefix ../notebook-generator/
npm run test --prefix ../notebook-generator/

# underscores in file names look bad in hackpack, so this
# replaces all underscores with spaces
# note, this is the perl `rename` command, not the linux util
#find ../library/ -depth -execdir rename 'y/_/ /' {} +

# regarding school branding: https://brand.sdsmt.edu/identity/our-name/
# in particular, no initials
# logo taken from https://brand.sdsmt.edu/identity/official-logos/
./../notebook-generator/bin/notebookgen ../library/ --author "South Dakota Mines" --output ./hackpack.pdf --size 8 --columns 3 --image .config/SouthDakotaMinesLogo.png
