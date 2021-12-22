# Programming-Team-Code

Yet another competitive programming repo. Directory structure inspired by [KACTL](https://github.com/kth-competitive-programming/kactl):

- [content/](https://github.com/lrvideckis/Programming-Team-Code/tree/master/content) for copy-pastable c++ code
- [template.cpp](https://github.com/lrvideckis/Programming-Team-Code/blob/master/template.cpp), although all code *should* work with just `typedef long long ll;`
  - Note the `#define int long long` -> WA from overflow too many times 😅. All library code is tested *without* this `#define`, so feel free to remove it.

## Testing

- All code compiled with flags: `g++ -Wall -Wextra -pedantic -Wno-unused-result -Wfatal-errors -DLOCAL -std=c++2a -O2 -Wshadow -Wformat=2 -Wfloat-equal -Wcast-qual -Wcast-align -fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all -fstack-protector` from [Catching silly mistakes with GCC](https://codeforces.com/blog/entry/15547)
  - TODO: add `-Wconversion` and fix all warnings
- *Most* code submitted on various online judges (in particular [Library Checker](https://judge.yosupo.jp/))
- [stress-tests](https://github.com/lrvideckis/Programming-Team-Code/tree/master/stress-tests) which compares library code output to a naive version (or another alg) on random inputs (run with CI on every commit).

## Coding style

I aim for a balance between best coding practices, speed (runtime), and ease of modifiability.

- minimal `#define`'s and `typedef`'s for ease of use & readability & modifiability
- prefering structs & functions over globals to keep a clean scope
- [tabs](https://youtu.be/SsoOG6ZeyUI) (fight me)

## Out of scope

- [Geometry](https://github.com/kth-competitive-programming/kactl/tree/main/content/geometry), [math stuff](https://github.com/kth-competitive-programming/kactl/tree/main/content/numerical), [2-sat](https://github.com/kth-competitive-programming/kactl/blob/main/content/graph/2sat.h) - I use KACTL's version of these
