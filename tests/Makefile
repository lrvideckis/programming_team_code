help:
	@echo "command                        | explanation"
	@echo "------------------------------ | -----------"
	@echo "make compile_all_tests         | compile all tests with g++ for warnings"
	@echo
	@echo "make astyle_cppcheck_clangtidy | runs astyle, cppcheck, clang-tidy (verifies snake case)"
	@echo
	@echo "make find_files_without_tests  | print list of all .hpp files included by *no* .test.cpp files"
	@echo "                               |   - these files are not compiled nor linted as part of ci"
	@echo
	@echo "make doxygen                   | check correctness, completeness of doxygen comments"
	@echo
	@echo "make hackpack                  | build hackpack.pdf from .tex file"
	@echo
	@echo "make format_bash_scripts       | format & simplify bash scripts"

compile_all_tests:
	./scripts/compile_all_tests.sh

astyle_cppcheck_clangtidy:
	./scripts/astyle_cppcheck_clangtidy.sh

find_files_without_tests:
	./scripts/find_files_without_tests.sh

doxygen:
	./scripts/doxygen.sh

hackpack:
	./scripts/hackpack.sh

format_bash_scripts:
	./scripts/format_bash_scripts.sh
