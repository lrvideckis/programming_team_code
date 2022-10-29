#! /bin/bash

! grep --only-matching --fixed-strings --file=<(find ../library/ -type f -name "*.hpp") scripts/hackpack.tex \
	| grep --invert-match --fixed-strings --file=- <(find ../library/ -type f -name "*.hpp")
