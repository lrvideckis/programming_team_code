help:
	@echo "Available commands                   | explanation"
	@echo "------------------------------------ | -----------"
	@echo "make compile_all_tests               | compile all tests with g++"
	@echo
	@echo "make check_format                    | runs Astyle, cppcheck, clang-tidy (verifies snake case)"
	@echo
	@echo "make print_untested_files            | print list of all .hpp files included by *no* .test.cpp files"
	@echo "                                     |   - These files are not compiled nor linted as part of CI."
	@echo "                                     |   - Need to add symlink first."
	@echo
	@echo "make print_tests_by_git_modification | print list of all .test.cpp files ordered by most recently modified."
	@echo "                                     |   - Determines modified date from \"git log\". So when running locally,"
	@echo "                                     |       you need to locally commit any file for it to appear first on this list."
	@echo "                                     |   - Need to add symlink first."
	@echo
	@echo "make add_symlink                     | to fix ac-library include paths."
	@echo "                                     |   - Need to initialize git submodules first."
	@echo
	@echo "make hackpack                        | build hackpack from .tex file"
	@echo
	@echo "make help                            | to show this information"

compile_all_tests:
	./scripts/compile_all_tests.sh

check_format:
	./scripts/check_format.sh

print_untested_files:
	./scripts/find_files_without_tests.sh

print_tests_by_git_modification:
	./scripts/tests_by_git_modification.sh

add_symlink:
	./scripts/add_symlink.sh

hackpack:
	./scripts/make_hackpack.sh
