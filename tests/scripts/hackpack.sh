#!/usr/bin/env bash

#takes in file name
remove_pragma_add_hash() {
	sed --in-place '/#pragma once/d' $1

	hash=$(cat $1 | ../library/contest/hash.sh)
	comment="cat $(basename $1) | ./hash.sh"
	sed --in-place "1s;^;//$comment\n//$hash\n;" $1
}
find ../library/ -type f -name "*.hpp" -exec remove_pragma_add_hash {} \;

#needed to make boxes under headings empty, otherwise you get filler text
touch NULL

#need to compile twice for it to generate the table of contents
#I think it's related to not knowing page numbers until after first pdf generation
pdflatex scripts/hackpack.tex
pdflatex scripts/hackpack.tex

mv hackpack.pdf ../

#takes in file name
remove_hash_add_pragma() {
	sed --in-place '1,2d' $1
	sed --in-place '1 i\#pragma once' $1
}
find ../library/ -type f -name "*.hpp" -exec remove_hash_add_pragma {} \;

rm NULL hackpack.aux hackpack.lol hackpack.log
