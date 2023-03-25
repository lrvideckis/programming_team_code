#!/usr/bin/env bash
set -euo pipefail

shellcheck --shell=bash scripts/*.sh || exit 1

find ../library/ scripts/ -type f -name "*.sh" -print0 |
	xargs shfmt -ln=bash -s -d -w
