#!/bin/bash
# ** glob now searches any number of levels
shopt -s globstar

git submodule init
git submodule update

for file in ../library/**/*.sh ../library/**/*.md ../library/**/*.cpp; do
	new_path=${file//library/chicken}
	mkdir --parents "$(dirname "$new_path")"
	cp "$file" "$new_path"
done

for header in ../library/**/*.hpp; do
	new_path=${header//library/chicken}
	mkdir --parents "$(dirname "$new_path")"
	cpp -nostdinc -C -P "$header" "$new_path"
done
mv ../library/ ../library_old/
mv ../chicken/ ../library/
# the cpp preprocessor sometimes leaves blank empty lines
sed --in-place '/^[[:space:]]*$/d' ../library/**/*.hpp
# remove `/** @file */` comments
sed --in-place '/^\/\*\* @file \*\/$/d' ../library/**/*.hpp
