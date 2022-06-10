# programming_team_code

Yet another competitive programming repo. Quick links:

- [library/](https://github.com/lrvideckis/programming_team_code/tree/master/library)
- [template.cpp](https://github.com/lrvideckis/programming_team_code/blob/master/template.cpp)
- [25_pg_reference.pdf](https://github.com/lrvideckis/programming_team_code/blob/master/25_pg_reference.pdf)

## Testing
[![Actions Status](https://github.com/lrvideckis/programming_team_code/workflows/verify/badge.svg)](https://github.com/lrvideckis/programming_team_code/actions)

see [tests/README.md](https://github.com/lrvideckis/programming_team_code/blob/master/tests/README.md)

## Format

1. (optional) Run the following from [library/](https://github.com/lrvideckis/programming_team_code/tree/master/library) to remove all comments and asserts. (for advanced users)
   ```
   find . -type f -name "*.h" -exec bash -c "sed --in-place --expression '/^#pragma/d' --expression '/assert/d' {}; cpp -fpreprocessed -P {} > tmp; mv tmp {}" \;
   ```

2. Run the following from [library/](https://github.com/lrvideckis/programming_team_code/tree/master/library) to format. [astyle wiki](http://astyle.sourceforge.net/astyle.html)
   ```
   astyle --indent=tab --style=attach --remove-braces --align-reference=type --align-pointer=type --delete-empty-lines --attach-classes --pad-oper --pad-header --unpad-paren --close-templates --indent-col1-comments --suffix=none --recursive "*.h"
   ```

## License

Everything is under [CC0](https://creativecommons.org/publicdomain/zero/1.0/).

## Out of scope

see [library/README.md](https://github.com/lrvideckis/programming_team_code/blob/master/library/README.md)

## Other CP repos

- https://github.com/kth-competitive-programming/kactl (one of the best)
- https://github.com/ShahjalalShohag/code-library
- https://github.com/ecnerwala/cp-book
- https://github.com/the-tourist/algo
- https://github.com/nealwu/competitive-programming
- https://github.com/dacin21/dacin21_codebook
- https://github.com/yosupo06/library-checker-problems
- https://github.com/ucf-programming-team/hackpack-cpp
