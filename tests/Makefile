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
	@echo "make astyle_cppcheck_clangtidy       | runs astyle, cppcheck, clang-tidy (verifies snake case)"
	@echo "                                     |   - ditto above but \`clang-tidy\` instead of \`g++\`"
	@echo
	@echo "make find_files_without_tests        | print list of all .hpp files included by *no* .test.cpp files"
	@echo "                                     |   - these files are not compiled nor linted as part of ci."
	@echo "                                     |   - need to initialize git submodules first."
	@echo
	@echo "make hackpack                        | build hackpack from .tex file"
	@echo
	@echo "make help                            | to show this information"

compile_all_tests:
	./scripts/compile_all_tests.sh

astyle_cppcheck_clangtidy:
	./scripts/astyle_cppcheck_clangtidy.sh

find_files_without_tests:
	./scripts/find_files_without_tests.sh

hackpack:
	./scripts/hackpack.sh
