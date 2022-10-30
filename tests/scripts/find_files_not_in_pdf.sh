#! /bin/bash

#source: https://unix.stackexchange.com/a/194702

! grep --only-matching --fixed-strings --file=<(find ../library/ -type f -name "*.hpp") scripts/hackpack.tex \
	| grep --invert-match --fixed-strings --file=- <(find ../library/ -type f -name "*.hpp")
