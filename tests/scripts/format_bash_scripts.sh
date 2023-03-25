#!/usr/bin/env bash
set -euo pipefail

find ../library/ scripts/ -type f -name "*.sh" |
	xargs shfmt -ln=bash -s -d -w
