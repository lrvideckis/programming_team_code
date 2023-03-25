#!/usr/bin/env bash
set -euo pipefail

shellcheck --shell=bash --enable=check-set-e-suppressed,quote-safe-variables scripts/*.sh || exit 1

shfmt -ln=bash -s -d -w scripts/*.sh || exit 1
