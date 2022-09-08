# programming_team_code

My library of algorithms for competitive programming. Quick links:

- [library/](https://github.com/lrvideckis/programming_team_code/tree/master/library)
- [template.cpp](https://github.com/lrvideckis/programming_team_code/blob/master/library/contest/template.cpp)
- [hackpack.pdf](https://github.com/lrvideckis/programming_team_code/blob/master/hackpack.pdf)

## Testing
[![Actions Status](https://github.com/lrvideckis/programming_team_code/workflows/verify/badge.svg)](https://github.com/lrvideckis/programming_team_code/actions)

see [tests/README.md](https://github.com/lrvideckis/programming_team_code/blob/master/tests/README.md)

## Format

1. (optional) Run the following from [library/](https://github.com/lrvideckis/programming_team_code/tree/master/library) to remove all comments and asserts. (for advanced users)
   ```
   find . -type f -name "*.hpp" -exec bash -c "sed --in-place --expression '/^#pragma/d' --expression '/assert/d' {}; cpp -fpreprocessed -P {} > tmp; mv tmp {}" \;
   ```

2. Run the following from [library/](https://github.com/lrvideckis/programming_team_code/tree/master/library) to format. [astyle wiki](http://astyle.sourceforge.net/astyle.html)
   ```
   astyle --indent=tab --style=attach --remove-braces --align-reference=type --align-pointer=type --delete-empty-lines --attach-classes --pad-oper --pad-header --unpad-paren --close-templates --indent-col1-comments --suffix=none --recursive "*.hpp"
   ```

## License

I've added links to sources when applicable. Everything is under the [CC0 license](https://creativecommons.org/publicdomain/zero/1.0/), so use/take anything with no strings attached.

## Other CP repos

- https://github.com/kth-competitive-programming/kactl (one of the best)
- https://github.com/yosupo06/Algorithm (also one of the best)
- https://github.com/ShahjalalShohag/code-library
- https://github.com/ecnerwala/cp-book
- https://github.com/the-tourist/algo
- https://github.com/nealwu/competitive-programming
- https://github.com/dacin21/dacin21_codebook
- https://github.com/ucf-programming-team/hackpack-cpp
