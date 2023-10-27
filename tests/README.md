## Run on each commit:
command | settings | notes | see
--- | --- | --- | ---
oj-verify | [config.toml](../.verify-helper/config.toml) | <ul><li>Run from `programming_team_code/` to enable `config.toml` settings, else disabled.</li><li>[Check/Delete] [timestamps.remote.json](../.verify-helper/timestamps.remote.json) to [see which tests ran/re-run all tests].</li></ul> | <ul><li>https://online-judge-tools.github.io/verification-helper/document.html</li><li>https://online-judge-tools.github.io/verification-helper/installer.html</li><li>[Library Checker](https://judge.yosupo.jp/)</li><li>[Aizu Online Judge](https://onlinejudge.u-aizu.ac.jp/courses/list)</li></ul>
g++ | [.config/.gcc_compile_flags](.config/.gcc_compile_flags) | <ul><li>`-std=c++17` since some judges still have this version</li><li>`-Wsign-conversion` is out of scope</li><li>`-Werror` treats warnings as errors to make CI fail</li></ul> | <ul><li>https://codeforces.com/blog/entry/15547</li><li>https://codeforces.com/blog/entry/79024</li><li>https://codeforces.com/blog/entry/74032</li></ul>
astyle | [.config/.astylerc](.config/.astylerc) | running `make astyle_cppcheck` locally will format files | http://astyle.sourceforge.net/astyle.html
cppcheck | [.config/.cppcheck_suppression_list](.config/.cppcheck_suppression_list), also see flags in cppcheck command in [scripts/astyle_cppcheck.sh](scripts/astyle_cppcheck.sh) | | https://cppcheck.sourceforge.io/
clang-tidy | [.config/.clang-tidy](.config/.clang-tidy) | checks variables for snake_case | https://clang.llvm.org/extra/clang-tidy/checks/list.html
doxygen | [.config/Doxyfile](.config/Doxyfile) | <ul><li>Used mainly as a style guide</li><li>Not run on tests (only on headers)</li></ul> | <ul><li>https://www.doxygen.nl/manual/commands.html</li><li>https://www.doxygen.nl/manual/docblocks.html</li></ul>
notebook-generator | see flags in command in [scripts/hackpack.sh](scripts/hackpack.sh) | creates hackpack.pdf | https://github.com/pin3da/notebook-generator 
shellcheck | see flags in [scripts/shellcheck_shfmt.sh](scripts/shellcheck_shfmt.sh) | linter for bash scripts | https://www.shellcheck.net/
shfmt | see flags in [scripts/shellcheck_shfmt.sh](scripts/shellcheck_shfmt.sh) | formatter for bash scripts | https://github.com/mvdan/sh

## Cron jobs:
1) [rerun_lib_checker_tests_daily.yml](../.github/workflows/rerun_lib_checker_tests_daily.yml) runs at midnight (PDT) and removes the file [timestamps.remote.json](../.verify-helper/timestamps.remote.json)
2) [run_tests_scheduled.yml](../.github/workflows/run_tests_scheduled.yml) runs `oj-verify all` every 30 minutes between midnight and 5am.
3) [check_all_tests_ran.yml](../.github/workflows/check_all_tests_ran.yml) runs at 5am and checks that all tests have run.

- Main reason 1: occasionally Library Checker [adds new tests](https://github.com/yosupo06/library-checker-problems/issues?q=label%3Atestcase). So now that the lib is re-tested daily, it will be tested on any newly-added tests.
- Main reason 2: sometimes I do a code-mod style change which affects many files, and causes many tests to have to be re-run. But `oj-verify all` only tests about 10-20 tests at a time meaning not all tests will be re-run. So these cron jobs mean I don't have to worry about manually making timely commits to rerun all tests.
- Side reason: Library Checker generates tests randomly, so more testing means the code is tested on more random data.

## Makefile
to see commands:
```
make help
```
