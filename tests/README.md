All commands (except doxygen) run *only* on `*.test.cpp` files in [library_checker_aizu_tests/](library_checker_aizu_tests/) (thus also *included* `*.hpp` files in [library/](../library/)).
  - Reason: `*.hpp` files don't have includes (because CP) which some of these tools need. Also this way incentivizes adding tests.
    - BTW kactl addresses this problem by [manually adding includes](https://github.com/kth-competitive-programming/kactl/blob/main/doc/scripts/test-compiles.sh) to header files, then [compiling](https://github.com/kth-competitive-programming/kactl/blob/main/doc/scripts/compile-all.sh) the modified headers.
  - see `make find_files_without_tests` for `*.hpp` files which are not included by any `*.test.cpp` file


command | settings | notes | see
--- | --- | --- | ---
oj-verify | [config.toml](../.verify-helper/config.toml) | <ul><li>Run from `programming_team_code/` to enable `config.toml` settings, else disabled.</li><li>[Check/Delete] [timestamps.remote.json](../.verify-helper/timestamps.remote.json) to [see which tests ran/re-run all tests].</li></ul> | <ul><li>https://online-judge-tools.github.io/verification-helper/document.html</li><li>https://online-judge-tools.github.io/verification-helper/installer.html</li><li>[Library Checker](https://judge.yosupo.jp/)</li><li>[Aizu Online Judge](https://onlinejudge.u-aizu.ac.jp/courses/list)</li></ul>
g++ | [.config/.gcc_compile_flags](.config/.gcc_compile_flags) | <ul><li>`-std=c++17` since some judges still have this version</li><li>`-Wsign-conversion` is out of scope</li><li>`-Werror` treats warnings as errors to make CI fail</li></ul> | <ul><li>https://codeforces.com/blog/entry/15547</li><li>https://codeforces.com/blog/entry/79024</li><li>https://codeforces.com/blog/entry/74032</li></ul>
astyle | [.config/.astylerc](.config/.astylerc) | running `make astyle_cppcheck` locally will format files | http://astyle.sourceforge.net/astyle.html
cppcheck | [.config/.cppcheck_suppression_list](.config/.cppcheck_suppression_list), also see flags in cppcheck command in [scripts/astyle_cppcheck.sh](scripts/astyle_cppcheck.sh) | | https://cppcheck.sourceforge.io/
clang-tidy | [.config/.clang-tidy](.config/.clang-tidy) | checks variables for snake_case | https://clang.llvm.org/extra/clang-tidy/checks/list.html
doxygen | [.config/Doxyfile](.config/Doxyfile) | <ul><li>Used mainly as a style guide</li><li>Not run on tests (only on headers)</li></ul> | <ul><li>https://www.doxygen.nl/manual/commands.html</li><li>https://www.doxygen.nl/manual/docblocks.html</li></ul>
notebook-generator | see flags in command in [scripts/hackpack.sh](scripts/hackpack.sh) | creates hackpack.pdf | https://github.com/pin3da/notebook-generator 

## Makefile
to see commands:
```
make help
```
