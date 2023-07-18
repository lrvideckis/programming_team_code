## No comments
See `no_comments` branch for the same code with all comments removed. The CI will keep this branch updated. You can remove all comments with:
```
cpp -fpreprocessed -P a.cpp a_no_comments.cpp
```
Although, note this will also remove `#define ssize(x) (int)(x).size()`

## Doxygen
Let's try to minimize the # of non-doxygen comments.

Needed for doxygen to see global functions
```
/** @file */
```
Place this directly before a struct or function.

```
/**
 * @see <link to some source>
 *
 * Name, description, and/or any notes/tricks. It's okay if this is multiple
 * lines; wrap like this.
 * @code{.cpp}
 *     //example usage or initialization
 *     vector<int> arr;
 * @endcode
 * @param le,ri defines range [le, ri)
 * @returns Sum of range.
 * @time O(n * sqrt(n log n)) I don't care about formatting as long as it's
 * clear. Ex: O(log n * k) could either mean O(log(n) * k) or O(log(nk)) - bad.
 * @space O(n ^ (3/2)) note space complexity is always <= time complexity
 * (unless you can travel back in time)
 */
```
for member vars:
`int var; /**< Inline description */`

run from `library/`
```
doxygen ../tests/Doxyfile |& grep seg_tree
```

## Things to consider when adding a new alg to the library
- How often have you seen it
- No good `type-ii` implementation elsewhere (usually KACTL), types:
    1. Longer codes for online contests like codeforces where you can copy paste
    2. Shorter, golfed codes for ICPC where you can't copy paste
- How hard to modify existing library code
- Easily testable (preferably there is a problem to test, instead of [handmade tests](../tests/library_checker_aizu_tests/handmade_tests)). These are the only judges whose problems can be used in CI: [library checker](https://judge.yosupo.jp/), [aizu judge](https://onlinejudge.u-aizu.ac.jp/courses/list)
