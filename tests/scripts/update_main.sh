#!/bin/bash
# ** glob now searches any number of levels
shopt -s globstar

git submodule init
git submodule update

mkdir ../chicken
cp --recursive ../library/. ../chicken

for header in ../chicken/**/*.hpp; do
	cpp -std=c17 -nostdinc -C -P "$header" "${header//chicken/library}"
done

# cpp command changes tabs to white space
astyle --options=.config/.astylerc --recursive "../library/*.hpp"

# the cpp preprocessor sometimes leaves blank empty lines
sed --in-place '/^[[:space:]]*$/d' ../library/**/*.hpp
# remove `/** @file */` comments
sed --in-place '/^\/\*\* @file \*\/$/d' ../library/**/*.hpp
# remove NOLINTNEXTLINE comments
sed --in-place '/^\/\/NOLINTNEXTLINE(readability-identifier-naming)$/d' ../library/**/*.hpp
