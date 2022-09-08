#!/usr/bin/env bash

#adds hash code comments
tests="$(find ../library -name "*.hpp") $(find ../ac-library/atcoder -name "*.hpp")"
for test in $tests
do
	hash=$(cat $test | ../library/contest/hash.sh)
	comment="cat $(basename $test) | ./hash.sh"
	sed --in-place "1s;^;//$comment\n//$hash\n;" $test
done


#needed to make boxes under headings empty. Else you get this weird text
touch null

#need to compile twice for it to generate the table of contents
#I think it's related to not knowing page numbers until after first pdf generation
pdflatex scripts/hackpack.tex
pdflatex scripts/hackpack.tex

mv hackpack.pdf ../

#removes hash code comments
for test in $tests
do
	sed --in-place '1,2d' $test
done
