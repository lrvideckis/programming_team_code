#!/usr/bin/env bash

#adds hash code comments
for test in $(find ../library/ -type f -name "*.hpp")
do
	hash=$(cat $test | ../library/contest/hash.sh)
	comment="cat $(basename $test) | ./hash.sh"
	sed --in-place "1s;^;//$comment\n//$hash\n;" $test
done

#needed to make boxes under headings empty, otherwise you get filler text
touch NULL

#need to compile twice for it to generate the table of contents
#I think it's related to not knowing page numbers until after first pdf generation
pdflatex scripts/hackpack.tex
pdflatex scripts/hackpack.tex

mv hackpack.pdf ../

#removes hash code comments
find ../library/ -type f -name "*.hpp" \
	| xargs sed --in-place "1,2d"

rm NULL hackpack.aux hackpack.lol hackpack.log
