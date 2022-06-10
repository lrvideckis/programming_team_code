help:
	@echo "Available commands                         | explanation"
	@echo "------------------------------------------ | -----------"
	@echo "make test                                  | to run all the stress tests in stress_tests/"
	@echo "make test which_test=<name_of_test_file>   | runs only the specified test"
	@echo "make test_compiles                         | to test compiling all headers"
	@echo "make test_compiles which_alg=<name_of_alg> | to test compiling a single alg"
	@echo "make verify_library_checker_test_comments  | check library checker test status comments in .h files"
	@echo "make verify_stress_test_comments           | check stress test status comments in .h files"
	@echo "make pdf                                   | build PDF from .tex file"
	@echo "make test_format                           | checks code is formatted with astyle"
	@echo "make check_snake_case                      | verify all code+file names are snake case"
	@echo "make help                                  | to show this information"

test:
	./scripts/run_all.sh . $(which_test)

test_compiles:
	./scripts/compile_all.sh . $(which_alg)

verify_library_checker_test_comments:
	./scripts/library_checker_test_comments.sh .

verify_stress_test_comments:
	./scripts/stress_test_comments.sh .

pdf:
	./scripts/make_pdf.sh .

test_format:
	./scripts/test_format.sh .

check_snake_case:
	./scripts/check_snake_case.sh .
