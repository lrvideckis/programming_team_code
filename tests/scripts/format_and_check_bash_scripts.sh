#!/usr/bin/env bash
set -euo pipefail

shellcheck --shell=bash scripts/*.sh || exit 1

shfmt -ln=bash -s -d -w scripts/*.sh || exit 1
