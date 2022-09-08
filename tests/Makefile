help:
	@echo "Available commands                         | explanation"
	@echo "------------------------------------------ | -----------"
	@echo "make check_format                          | verify snake case, and Astyle format"
	@echo "make print_untested_files                  | print list of all .h files with no tests"
	@echo "make add_symlink                           | to fix ac-library includes"
	@echo "make hackpack                              | build hackpack from .tex file"
	@echo "make help                                  | to show this information"

check_format:
	./scripts/check_format.sh .

print_untested_files:
	./scripts/find_files_without_tests.sh

add_symlink:
	./scripts/add_symlink.sh

hackpack:
	./scripts/make_hackpack.sh .
