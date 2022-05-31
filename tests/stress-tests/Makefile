help:
	@echo "This makefile builds my algorithms repo"
	@echo ""
	@echo "Available commands are:"
	@echo "	make test                                  - to run all the stress tests in stress-tests/"
	@echo "	make test which_test=<name_of_test_file>   - runs only the specified test"
	@echo "	make test-compiles                         - to test compiling all headers"
	@echo "	make test-compiles which_alg=<name_of_alg> - to test compiling a single alg"
	@echo "	make verify-library-checker-test-comments  - check library checker test status comments in .h files"
	@echo "	make verify-stress-test-comments           - check stress test status comments in .h files"
	@echo "	make pdf                                   - build PDF from .tex file"
	@echo "	make help                                  - to show this information"

test:
	./scripts/run-all.sh . $(which_test)

test-compiles:
	./scripts/compile-all.sh . $(which_alg)

verify-library-checker-test-comments:
	./scripts/library_checker_test_comments.sh .

verify-stress-test-comments:
	./scripts/stress_test_comments.sh .

pdf:
	./scripts/add_hash_code_comments.sh .

