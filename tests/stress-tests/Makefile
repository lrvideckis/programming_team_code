help:
	@echo "This makefile builds my algorithms repo"
	@echo ""
	@echo "Available commands are:"
	@echo "	make test                                  - to run all the stress tests in stress-tests/"
	@echo "	make test which_test=<name_of_test_file>   - runs only the specified test"
	@echo "	make test-compiles                         - to test compiling all headers"
	@echo "	make test-compiles which_alg=<name_of_alg> - to test compiling a single alg"
	@echo "	make verify-test-comments                  - check test status comments in .h files"
	@echo "	make help                                  - to show this information"

test:
	./scripts/run-all.sh . $(which_test)

test-compiles:
	./scripts/compile-all.sh . $(which_alg)

verify-test-comments:
	./scripts/test_status_checker.sh .
