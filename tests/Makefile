help:
	@echo "Available commands                         | explanation"
	@echo "------------------------------------------ | -----------"
	@echo "make test_compiles                         | to test compiling all headers"
	@echo "make test_compiles which_alg=<name_of_alg> | to test compiling a single alg"
	@echo "make pdf                                   | build PDF from .tex file"
	@echo "make push_pdf                              | push PDF to remote"
	@echo "make test_format                           | checks code is formatted with astyle"
	@echo "make check_snake_case                      | verify all code+file names are snake case"
	@echo "make print_untested_files                  | print list of all .h files with no tests"
	@echo "make help                                  | to show this information"

test_compiles:
	./scripts/compile_all.sh . $(which_alg)

pdf:
	./scripts/make_pdf.sh .

push_pdf:
	./scripts/push_pdf.sh .

test_format:
	./scripts/test_format.sh .

check_snake_case:
	./scripts/check_snake_case.sh .

print_untested_files:
	./scripts/find_files_without_tests.sh
