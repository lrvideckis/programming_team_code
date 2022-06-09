help:
	@echo "Available commands                         | explanation"
	@echo "------------------------------------------ | -----------"
	@echo "make test                                  | to run all the stress tests in stress-tests/"
	@echo "make test which_test=<name_of_test_file>   | runs only the specified test"
	@echo "make test-compiles                         | to test compiling all headers"
	@echo "make test-compiles which_alg=<name_of_alg> | to test compiling a single alg"
	@echo "make verify-library-checker-test-comments  | check library checker test status comments in .h files"
	@echo "make verify-stress-test-comments           | check stress test status comments in .h files"
	@echo "make pdf                                   | build PDF from .tex file"
	@echo "make test-format                           | checks code is formatted with astyle"
	@echo "make help                                  | to show this information"

test:
	./scripts/run-all.sh . $(which_test)

test-compiles:
	./scripts/compile-all.sh . $(which_alg)

verify-library-checker-test-comments:
	./scripts/library_checker_test_comments.sh .

verify-stress-test-comments:
	./scripts/stress_test_comments.sh .

pdf:
	./scripts/make_pdf.sh .

test-format:
	./scripts/test-format.sh .
