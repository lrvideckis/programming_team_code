help:
	@echo "This makefile builds my algorithms repo"
	@echo ""
	@echo "Available commands are:"
	@echo "	make test		- to run all the stress tests in stress-tests/"
	@echo "	make test-compiles	- to test compiling all headers"
	@echo "	make help		- to show this information"

test:
	./scripts/run-all.sh .

test-compiles:
	./scripts/compile-all.sh .
