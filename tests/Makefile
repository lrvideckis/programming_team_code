help:
	@echo "available commands                   | explanation"
	@echo "------------------------------------ | -----------"
	@echo "make compile_all_tests               | compile all tests with g++"
	@echo "                                     |   - since g++ takes a full ~5 +-1 minutes to compile everything,"
	@echo "                                     |     this will compile all *.test.cpp files in order of"
	@echo "                                     |     latest git modification date. so you have to first"
	@echo "                                     |               ***locally commit***"
	@echo "                                     |     the file for it to be compiled first."
	@echo
	@echo "make check_format                    | runs astyle, cppcheck, clang-tidy (verifies snake case)"
	@echo "                                     |   - ditto above but \`clang-tidy\` instead of \`g++\`"
	@echo
	@echo "make find_files_without_tests        | print list of all .hpp files included by *no* .test.cpp files"
	@echo "                                     |   - these files are not compiled nor linted as part of ci."
	@echo "                                     |   - need to initialize git submodules first."
	@echo
	@echo "make find_files_not_in_pdf           | print list of all .hpp files *not* included by scripts/hackpack.tex"
	@echo "                                     |   - these files are not included in the hackpack."
	@echo
	@echo "make tests_by_git_modification       | print list of all .test.cpp files ordered by most recently modified."
	@echo "                                     |   - determines modified date from \`git log\`. so when running locally,"
	@echo "                                     |       you need to locally commit any file for it to appear first on this list."
	@echo "                                     |   - need to initialize git submodules first."
	@echo
	@echo "make hackpack                        | build hackpack from .tex file"
	@echo
	@echo "make help                            | to show this information"

compile_all_tests:
	./scripts/compile_all_tests.sh

check_format:
	./scripts/check_format.sh

find_files_without_tests:
	./scripts/find_files_without_tests.sh

find_files_not_in_pdf:
	./scripts/find_files_not_in_pdf.sh

tests_by_git_modification:
	./scripts/tests_by_git_modification.sh

hackpack:
	./scripts/hackpack.sh
