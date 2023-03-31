#!/bin/bash
# http://redsymbol.net/articles/unofficial-bash-strict-mode/
set -euo pipefail

#adds hash code comments
for header in ../library/**/*.hpp; do
	hash=$(../library/contest/hash.sh <"$header")
	comment="cat $(basename "$header") | ./hash.sh"
	sed --in-place "1s;^;//$comment\n//$hash\n;" "$header"
done

#needed to make boxes under headings empty, otherwise you get filler text
touch NULL

#need to compile twice for it to generate the table of contents
#I think it's related to not knowing page numbers until after first pdf generation
pdflatex -halt-on-error .config/hackpack.tex || exit 1
pdflatex -halt-on-error .config/hackpack.tex || exit 1

#remove hash code comments
sed -i '1,2d' ../library/**/*.hpp
