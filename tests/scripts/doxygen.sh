#!/usr/bin/env bash

cd ../library/
doxygen ../tests/Doxyfile
python3 -m coverxygen --xml-dir xml/ --src-dir . --output - --kind file \
	--format json-summary | ./../tests/scripts/parse_coverxygen.py
