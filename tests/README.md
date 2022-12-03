All commands (except doxygen) run *only* on `*.test.cpp` files in [online_judge_tests/](online_judge_tests/) (thus also *included* `*.hpp` files in [library/](../library/)).
  - Reason: `*.hpp` files don't have includes (because CP) which some of these tools need. Also this way incentivizes adding tests.
    - BTW kactl addresses this problem by [manually adding includes](https://github.com/kth-competitive-programming/kactl/blob/main/doc/scripts/test-compiles.sh) to header files, then [compiling](https://github.com/kth-competitive-programming/kactl/blob/main/doc/scripts/compile-all.sh) the modified headers. But IMO it's safer to leave the headers un-touched.
  - see `make find_files_without_tests` for `*.hpp` files which are not included by any `*.test.cpp` file.


command | settings | notes | see
--- | --- | --- | ---
oj-verify | [config.toml](../.verify-helper/config.toml) | <ul><li>Run from `programming_team_code/tests/` to enable `config.toml` settings, else disabled.</li><li>[Check/Delete] [timestamps.remote.json](../.verify-helper/timestamps.remote.json) to [see which tests ran/re-run all tests].</li></ul> | <ul><li>https://online-judge-tools.github.io/verification-helper/document.html</li><li>https://online-judge-tools.github.io/verification-helper/installer.html</li><li>[Library Checker](https://judge.yosupo.jp/)</li><li>[Aizu Online Judge](https://onlinejudge.u-aizu.ac.jp/courses/list)</li></ul>
g++ | [.gcc_compile_flags](.gcc_compile_flags) | <ul><li>`-std=c++17` since some judges still have this version</li><li>`-Wsign-conversion` is out of scope</li><li>`-Werror` treats warnings as errors to make CI fail</li></ul> | <ul><li>https://codeforces.com/blog/entry/15547</li><li>https://codeforces.com/blog/entry/79024</li></ul>
astyle | [.astylerc](.astylerc) | running `make astyle_cppcheck_clangtidy` locally will format files | http://astyle.sourceforge.net/astyle.html
cppcheck | [.cppcheck_suppression_list](.cppcheck_suppression_list), also see flags in cppcheck command in [scripts/astyle_cppcheck_clangtidy.sh](scripts/astyle_cppcheck_clangtidy.sh) | | https://cppcheck.sourceforge.io/
clang-tidy | [.clang-tidy](.clang-tidy) | checks variables for snake_case | https://clang.llvm.org/extra/clang-tidy/checks/list.html
doxygen | [Doxyfile](Doxyfile) | <ul><li>Used mainly as a style guide</li><li>Not run on tests (only on headers)</li></ul> | <ul><li>https://www.doxygen.nl/manual/commands.html</li><li>https://www.doxygen.nl/manual/docblocks.html</li></ul> 

## Makefile
to see commands:
```
make help
```
## Steps to add code from other repos to PDF
1. add other repo as a submodule
2. Include new file(s) in [scripts/hackpack.tex](scripts/hackpack.tex)
3. Add new file path(s) to [scripts/hackpack.sh](scripts/hackpack.sh) to include hash codes in PDF
4. build pdf
5. profit!
