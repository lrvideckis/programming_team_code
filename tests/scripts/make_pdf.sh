#!/usr/bin/env bash

./scripts/add_hash_code_comments.sh


#needed to make boxes under headings empty. Else you get this weird text
touch null

#need to compile twice for it to generate the table of contents
#I think it's related to not knowing page numbers after first pdf generation
pdflatex scripts/25_pg_reference.tex
pdflatex scripts/25_pg_reference.tex

mv 25_pg_reference.pdf ../


tests="$(find ../library -name "*.h")"

for test in $tests; do
	sed --in-place '1,3d' $test
done
