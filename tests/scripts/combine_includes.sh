#!/bin/bash
# http://redsymbol.net/articles/unofficial-bash-strict-mode/
set -euo pipefail
# ** glob now searches any number of levels
shopt -s globstar

for header in ../library/**/*.hpp; do
    new_path=$(echo $header | sed 's/library/chicken/')
    mkdir --parents $(dirname $new_path)
	cpp -nostdinc -C -P "$header" $new_path
done
mv ../library/ ../chicken2/
mv ../chicken/ ../library/
# the cpp preprocessor sometimes leaves blank empty lines
sed --in-place '/^[[:space:]]*$/d' ../library/**/*.hpp
