#!/bin/bash
# http://redsymbol.net/articles/unofficial-bash-strict-mode/
set -euo pipefail
# ** glob now searches any number of levels
shopt -s globstar

for header in ../library/**/*.hpp; do
    cpp -fpreprocessed -P "$header" temp_file
    mv temp_file "$header"
done
