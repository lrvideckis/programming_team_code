#!/usr/bin/env bash

find ../library/ scripts/ -type f -name "*.sh" |
	xargs shfmt -ln=bash -s -d -w
