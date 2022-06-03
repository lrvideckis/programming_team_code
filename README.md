# Programming-Team-Code

Yet another competitive programming repo. Quick links:

- [Library/](https://github.com/lrvideckis/Programming-Team-Code/tree/master/Library)
- [template.cpp](https://github.com/lrvideckis/Programming-Team-Code/blob/master/template.cpp)
- [25_pg-reference.pdf](https://github.com/lrvideckis/Programming-Team-Code/blob/master/25_pg-reference.pdf)

## Testing
[![Actions Status](https://github.com/lrvideckis/Programming-Team-Code/workflows/verify/badge.svg)](https://github.com/lrvideckis/Programming-Team-Code/actions)

see [tests/README.md](https://github.com/lrvideckis/Programming-Team-Code/blob/master/tests/README.md)

## Format

1. (optional) Run the following from [Library/](https://github.com/lrvideckis/Programming-Team-Code/tree/master/Library) to remove all comments and asserts. (for advanced users)
   ```
   find . -type f -name "*.h" -exec bash -c "sed --in-place --expression '/^#pragma/d' --expression '/assert/d' {}; cpp -fpreprocessed -P {} > tmp; mv tmp {}" \;
   ```

2. Run the following from [Library/](https://github.com/lrvideckis/Programming-Team-Code/tree/master/Library) to format. [astyle wiki](http://astyle.sourceforge.net/astyle.html)
   ```
   astyle --indent=tab --style=attach --remove-braces --align-reference=type --align-pointer=type --delete-empty-lines --attach-classes --pad-oper --pad-header --unpad-paren --close-templates --indent-col1-comments --suffix=none --recursive "*.h"
   ```

## License

Everything is under [CC0](https://creativecommons.org/publicdomain/zero/1.0/).

## Out of scope

see [Library/README.md](https://github.com/lrvideckis/Programming-Team-Code/blob/master/Library/README.md)

## Other CP repos

- https://github.com/kth-competitive-programming/kactl
- https://github.com/ShahjalalShohag/code-library
- https://github.com/ecnerwala/cp-book
- https://github.com/the-tourist/algo
- https://github.com/nealwu/competitive-programming
- https://github.com/dacin21/dacin21_codebook
- https://github.com/yosupo06/library-checker-problems
- https://github.com/ucf-programming-team/hackpack-cpp
