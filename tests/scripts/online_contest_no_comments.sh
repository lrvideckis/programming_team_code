#!/bin/bash
# ** glob now searches any number of levels
shopt -s globstar

git submodule init
git submodule update

for header in ../library/**/*.hpp; do
	new_path=${header//library/chicken}
	mkdir --parents "$(dirname "$new_path")"
	cpp -P "$header" "$new_path"
done
mv ../library/ ../library_old/
mv ../chicken/ ../library/

# cpp command changes tabs to white space
astyle --options=.config/.astylerc --recursive "../library/*.hpp"

# the cpp preprocessor sometimes leaves blank empty lines
sed --in-place '/^[[:space:]]*$/d' ../library/**/*.hpp
