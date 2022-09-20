help:
	@echo "Available commands                         | explanation"
	@echo "------------------------------------------ | -----------"
	@echo "make compile_all_tests                     | compile all tests with g++"
	@echo "make check_format                          | runs Astyle, cppcheck, clang-tidy (verifies snake case)"
	@echo "make print_untested_files                  | print list of all .h files with no tests"
	@echo "make print_tests_by_git_modification       | print list of all .h files with no tests"
	@echo "make add_symlink                           | to fix ac-library includes"
	@echo "make hackpack                              | build hackpack from .tex file"
	@echo "make help                                  | to show this information"

compile_all_tests:
	./scripts/compile_all_tests.sh .

check_format:
	./scripts/check_format.sh .

print_untested_files:
	./scripts/find_files_without_tests.sh

print_tests_by_git_modification:
	./scripts/tests_by_git_modification.sh

add_symlink:
	./scripts/add_symlink.sh

hackpack:
	./scripts/make_hackpack.sh .
