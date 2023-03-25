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

echo "bash scripts in tests/scripts/ missing set -euo pipefail:"
comm -23 --check-order <(
	find tests/scripts/ -type f -name "*.sh" |
		sort |
		uniq
) <(
	grep --recursive --fixed-strings --files-with-matches "set -euo pipefail" tests/scripts/ |
		sort |
		uniq
) |
	grep . &&
	exit 1

shellcheck --shell=bash --check-sourced --enable=check-set-e-suppressed,quote-safe-variables ./library/**/*.sh ./tests/**/*.sh || exit 1

shfmt -ln=bash -s -d -w ./library/**/*.sh ./tests/**/*.sh || exit 1
