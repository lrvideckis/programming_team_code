help:
	@echo "command                              | explanation"
	@echo "------------------------------------ | -----------"
	@echo "make compile_all_tests               | compile all tests with g++ for warnings"
	@echo
	@echo "make astyle_cppcheck                 | runs astyle, cppcheck"
	@echo
	@echo "make clangtidy                       | runs clang-tidy (mainly to verify snake case)"
	@echo
	@echo "make find_files_without_tests        | print list of all .hpp files included by *no* .test.cpp files"
	@echo "                                     |   - these files are not compiled nor linted as part of ci"
	@echo
	@echo "make doxygen                         | check correctness, completeness of doxygen comments"
	@echo
	@echo "make hackpack                        | build hackpack.pdf from .tex file"
	@echo
	@echo "make format_and_check_bash_scripts   | runs shfmt and shellcheck"
	@echo
	@echo "make online_contest_no_comments      | mainly to reduce code length"
	@echo
	@echo "make online_contest_comments         | for use in online contests"
	@echo
	@echo "make print_which_tests_havent_run    | to check if all tests have run"
	@echo
	@echo "make remove_randomly_generated_tests | removes lines from .verify-helper/timestamps.remote.json"
	@echo "                                     | corresponding to randomly generated tests. This will cause"
	@echo "                                     | these tests to eventually be re-run."

compile_all_tests:
	./scripts/compile_all_tests.sh

astyle_cppcheck:
	./scripts/astyle_cppcheck.sh

clangtidy:
	./scripts/clangtidy.sh

find_files_without_tests:
	./scripts/find_files_without_tests.sh

doxygen:
	./scripts/doxygen.sh

hackpack:
	./scripts/hackpack.sh

format_and_check_bash_scripts:
	./scripts/format_and_check_bash_scripts.sh

online_contest_no_comments:
	./scripts/online_contest_no_comments.sh

online_contest_comments:
	./scripts/online_contest_comments.sh

print_which_tests_havent_run:
	./scripts/print_which_tests_havent_run.sh

remove_randomly_generated_tests:
	./scripts/remove_randomly_generated_tests.sh
