#!/usr/bin/env bash
set -euo pipefail

#adds hash code comments
for header in $(find ../library/ -type f -name "*.hpp"); do
	hash=$(cat $header | ../library/contest/hash.sh)
	comment="cat $(basename $header) | ./hash.sh"
	sed --in-place "1s;^;//$comment\n//$hash\n;" $header
done

#needed to make boxes under headings empty, otherwise you get filler text
touch NULL

#need to compile twice for it to generate the table of contents
#I think it's related to not knowing page numbers until after first pdf generation
pdflatex -halt-on-error .config/hackpack.tex || exit 1
pdflatex -halt-on-error .config/hackpack.tex || exit 1
