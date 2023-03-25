#!/bin/bash
set -euo pipefail

cd ../

echo "bash scripts missing the bash shebang:"
comm -23 --check-order <(
	find . -type f -name "*.sh" |
		sort |
		uniq
) <(
	grep --recursive --fixed-strings --files-with-matches "#!/bin/bash" . |
		sort |
		uniq
) |
	grep . &&
	exit 1

shellcheck --shell=bash --check-sourced --enable=check-set-e-suppressed,quote-safe-variables ./**/*.sh || exit 1

shfmt -ln=bash -s -d -w ./**/*.sh || exit 1
