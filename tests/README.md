## Testing
- We rely on online-judge-tools ([github](https://github.com/online-judge-tools/verification-helper)) which tests code on either [Library Checker](https://judge.yosupo.jp/) or [Aizu Online Judge](https://onlinejudge.u-aizu.ac.jp/courses/list) problems.
  - [steps to setup](https://online-judge-tools.github.io/verification-helper/installer.html) for your own repo.
- See `*.test.cpp` files in [online_judge_tests/](online_judge_tests/) for the actual tests.
  - Note: we don't compile with `-D_GLIBCXX_DEBUG` as it causes `string s; cin >> s;` to TLE (compiler bug).
- Note: < 30 tests run per commit, and currently there are > 40 tests. So for big changes (ex: code mod), CI may not test all changed files. To fix, I make random commits which change effectively nothing until all tests run. Check [timestamps.remote.json](../.verify-helper/timestamps.remote.json) to see which tests ran.
  - Trick: delete [timestamps.remote.json](../.verify-helper/timestamps.remote.json) to re-run all tests.

## Linting
All of this *only* runs on `*.test.cpp` files in [online_judge_tests/](online_judge_tests/) (thus also *included* `*.hpp` files in [library/](../library/)).
  - Reason: `*.hpp` files don't have includes (because CP) which the linters need. Also this way incentivizes adding tests. FWIW kactl addresses this problem by [copying around / modifying](https://github.com/kth-competitive-programming/kactl/blob/main/doc/scripts/test-compiles.sh) header files.
  - see `make print_untested_files` for `*.hpp` files which are not included by any `*.test.cpp` file.


command | settings | notes | see
--- | --- | --- | ---
oj-verify | [config.toml](../.verify-helper/config.toml) ||
g++ | [.gcc_compile_flags](.gcc_compile_flags) | <ul><li>`-std=c++17` since some judges still have this version</li><li>`-Werror` treats warnings as errors to make CI fail</li></ul> | https://codeforces.com/blog/entry/15547
astyle | [.astylerc](.astylerc) | running `make astyle_cppcheck_clangtidy` locally will format files | http://astyle.sourceforge.net/astyle.html
cppcheck | [.cppcheck_suppression_list](.cppcheck_suppression_list), also see flags in cppcheck command in [scripts/astyle_cppcheck_clangtidy.sh](scripts/astyle_cppcheck_clangtidy.sh) | | https://cppcheck.sourceforge.io/
clang-tidy | [.clang-tidy](.clang-tidy) | checks variables for snake_case | https://clang.llvm.org/extra/clang-tidy/checks/list.html
doxygen | [Doxyfile](Doxyfile) | <ul><li>*Not enforced by CI*. Used mainly as a style guide.</li><li>The generated docs are not useful in CP and unavaliable in ICPC contests, so I don't generate them.</li></ul> | https://www.doxygen.nl/manual/commands.html

## Makefile
to see commands:
```
make help
```
## Steps to add code from other repos to PDF
1. add other repo as a submodule
2. Include new file(s) in [scripts/hackpack.tex](scripts/hackpack.tex)
3. Add new file path(s) to [scripts/make_hackpack.sh](scripts/make_hackpack.sh) to include hash codes in PDF
4. build pdf
5. profit!
