help:
	@echo "Available commands                         | explanation"
	@echo "------------------------------------------ | -----------"
	@echo "make check_format                          | verify snake case, and Astyle format"
	@echo "make print_untested_files                  | print list of all .h files with no tests"
	@echo "make add_symlink                           | to fix ac-library includes"
	@echo "make pdf                                   | build PDF from .tex file"
	@echo "make push_pdf                              | push PDF to remote"
	@echo "make help                                  | to show this information"

check_format:
	./scripts/check_format.sh .

print_untested_files:
	./scripts/find_files_without_tests.sh

add_symlink:
	./scripts/add_symlink.sh

pdf:
	./scripts/make_pdf.sh .

push_pdf:
	./scripts/push_pdf.sh .
