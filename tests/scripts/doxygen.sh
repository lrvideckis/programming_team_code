#!/usr/bin/env bash

#this generates documentation in XML format with doxygen, then parses the XML
#with coverxygen.
cd ../library/
doxygen ../tests/Doxyfile

run_coverxygen() {
	python3 -m coverxygen --xml-dir xml/ --src-dir . --output - --kind \
		struct,function --format json-summary
}

run_coverxygen # to show output in CI
#run_coverxygen | ./../tests/scripts/parse_coverxygen.py # now parse it
