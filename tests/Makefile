help:
	@echo "Available commands                         | explanation"
	@echo "------------------------------------------ | -----------"
	@echo "make pdf                                   | build PDF from .tex file"
	@echo "make push_pdf                              | push PDF to remote"
	@echo "make check_format                          | verify all code+file names are snake case"
	@echo "make print_untested_files                  | print list of all .h files with no tests"
	@echo "make help                                  | to show this information"

pdf:
	./scripts/make_pdf.sh .

push_pdf:
	./scripts/push_pdf.sh .

check_format:
	./scripts/check_format.sh .

print_untested_files:
	./scripts/find_files_without_tests.sh
