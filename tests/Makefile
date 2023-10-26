help:
	@echo "command                              | Run in CI? | explanation"
	@echo "------------------------------------ | ---------- | -----------"
	@echo "make compile_gcc17                   | yes        | compile all tests with -std=c++17 for warnings"
	@echo "                                     |            |"
	@echo "make compile_gcc20                   | yes        | compile all tests with -std=c++20 without ssize macro for warnings"
	@echo "                                     |            |"
	@echo "make astyle_cppcheck                 | yes        | runs astyle, cppcheck"
	@echo "                                     |            |"
	@echo "make clangtidy                       | yes        | runs clang-tidy (mainly to verify snake_case)"
	@echo "                                     |            |"
	@echo "make doxygen                         | yes        | runs doxygen"
	@echo "                                     |            |"
	@echo "make hackpack                        | yes        | build hackpack.pdf from .tex file"
	@echo "                                     |            |"
	@echo "make shellcheck_shfmt                | yes        | runs shellcheck and shfmt"
	@echo "                                     |            |"
	@echo "make online_contest_no_comments      | yes        | 1) removes all comments"
	@echo "                                     |            | 2) copies included files into file"
	@echo "                                     |            | 3) pushes to online_contest_no_comments branch"
	@echo "                                     |            |"
	@echo "make online_contest_comments         | yes        | 1) copies included files into file"
	@echo "                                     |            | 2) pushes to online_contest_comments branch"
	@echo "                                     |            |"
	@echo "make remove_randomly_generated_tests | yes        | removes lines from .verify-helper/timestamps.remote.json"
	@echo "                                     |            | corresponding to randomly generated tests"
	@echo "                                     |            |   - used in daily cron job to re-run these tests daily"
	@echo "                                     |            |"
	@echo "make files_without_tests             | yes        | print list of all .hpp files included by *no* .test.cpp files"
	@echo "                                     |            |   - these files are not compiled nor linted as part of ci"
	@echo "                                     |            |"
	@echo "make print_which_tests_havent_run    | no         | mainly to check if all tests have run"

compile_gcc17:
	./scripts/compile_gcc17.sh

compile_gcc20:
	./scripts/compile_gcc20.sh

astyle_cppcheck:
	./scripts/astyle_cppcheck.sh

clangtidy:
	./scripts/clangtidy.sh

files_without_tests:
	./scripts/files_without_tests.sh

doxygen:
	./scripts/doxygen.sh

hackpack:
	./scripts/hackpack.sh

shellcheck_shfmt:
	./scripts/shellcheck_shfmt.sh

online_contest_no_comments:
	./scripts/online_contest_no_comments.sh

online_contest_comments:
	./scripts/online_contest_comments.sh

print_which_tests_havent_run:
	./scripts/print_which_tests_havent_run.sh

remove_randomly_generated_tests:
	./scripts/remove_randomly_generated_tests.sh
