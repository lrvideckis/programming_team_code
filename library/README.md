## Out of scope

- 2D data structures (like [seg tree](https://github.com/ShahjalalShohag/code-library/blob/master/Data%20Structures/Segment%20Tree%202D%20Dynamic.cpp), [sparse table](https://codeforces.com/blog/entry/45485) etc)
- [2-sat](https://github.com/kth-competitive-programming/kactl/blob/main/content/graph/2sat.h)
- [Chinese Remainder Theorem](https://github.com/kth-competitive-programming/kactl/blob/main/content/number-theory/CRT.h)
- [Convex Hull Trick](https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/LineContainer.h)
- [Dinic](https://github.com/ucf-programming-team/hackpack-cpp/blob/lightseba-general-changes/content/graphs/SebaDinic.h)
- [Disjoint set](https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/UnionFind.h)
- [DSU with rollback](https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/UnionFindRollback.h)
- [Fast Fourier transform](https://github.com/kth-competitive-programming/kactl/blob/main/content/numerical/FastFourierTransform.h)
- [fast IO](https://github.com/nealwu/competitive-programming/blob/master/io/io.cc) - I've never TLE'd specifically from IO slowness while using both  `cin.tie(0)->sync_with_stdio(0);` and `'\n'`
- [Floyd Warshall](https://github.com/kth-competitive-programming/kactl/blob/main/content/graph/FloydWarshall.h)
- [Geometry](https://github.com/kth-competitive-programming/kactl/tree/main/content/geometry)
- [Half Plane Intersection](https://github.com/ucf-programming-team/hackpack-cpp/blob/lightseba-general-changes/content/geometry/halfPlane.h)
- [Hilbert Mo](https://github.com/ucf-programming-team/hackpack-cpp/blob/lightseba-general-changes/content/misc/HilbertMos.h)
- [Interval container](https://github.com/kth-competitive-programming/kactl/blob/main/content/various/IntervalContainer.h)
- [Longest Increasing Subsequence](https://github.com/kth-competitive-programming/kactl/blob/main/content/various/LIS.h)
- [Manacher's](https://github.com/kth-competitive-programming/kactl/blob/main/content/strings/Manacher.h)
- [Matrix Operations](https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/Matrix.h)
- [Miller Rabin](https://github.com/kth-competitive-programming/kactl/blob/main/content/number-theory/MillerRabin.h)
- [Non-lazy seg tree](https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/SegmentTree.h)
- [polynomial stuff](https://cp-algorithms.com/algebra/polynomial.html)
- [queue with get max](https://github.com/ucf-programming-team/hackpack-cpp/blob/lightseba-general-changes/content/data-structures/MonotonicQueue.h)
- [SCC](https://github.com/kth-competitive-programming/kactl/blob/main/content/graph/SCC.h)
- [seg tree beats](https://codeforces.com/blog/entry/57319)
- [sqrt decomposition](https://github.com/nealwu/competitive-programming/blob/master/sqrt/search_buckets.cc) (search buckets)
- [string hashing](https://github.com/kth-competitive-programming/kactl/blob/main/content/strings/Hashing.h)
- [string rotational equivalence](https://github.com/kth-competitive-programming/kactl/blob/main/content/strings/MinRotation.h)
- [Suffix Array, LCP Array](https://github.com/ucf-programming-team/hackpack-cpp/blob/master/content/strings/SuffixArray.h)
- [Z function](https://github.com/kth-competitive-programming/kactl/blob/main/content/strings/Zfunc.h)
- [Suffix Tree](https://github.com/ucf-programming-team/hackpack-cpp/blob/master/content/strings/SuffixTree.h)
- [Sum Over Subsets with Convolution](https://github.com/ucf-programming-team/hackpack-cpp/blob/lightseba-general-changes/content/numerical/SumOverSubsets.h)

## Doxygen Format Guide

file comment
```
/**
 * @file
 * @brief Name or description.
 * @code{.cpp}
 *     //example usage or initialization
 * @endcode
 * @note Some note.
 * @trick Some trick.
 * @invariant Some invariant.
 * @see link to some source
 * @time O(n log n)
 * @memory O(n + m)
 */
```
function comment
```
/**
 * @brief For functions, usually this describes what the return value is. That
 * is okay. Let's not also include '@return' tag to be concise.
 * @time O(n log n)
 * @memory O(n + m)
 */
```

Notes:
- The only thing enforced by CI is the existance of a file comment for each
.hpp file. (I can change this to also verify function comments, but not for now.)
So not all tags are needed, but also it's up to us to stick to this style.
- No @author or @date tags: git history already stores this, so let's spend any effort maintaining this also in a comment.

## Things to consider when adding a new alg to the library
- How often have you seen it
- No good `type-ii` implementation elsewhere (usually KACTL), types:
    1. Longer codes for online contests like codeforces where you can copy paste
    2. Shorter codes for ICPC where you can't copy paste
- How hard to modify existing library code
- Easily testable (preferably there is a problem to test, instead of [handmade tests](../tests/online_judge_tests/handmade_tests)). These are the only judges whose problems can be used in CI: [library checker](https://judge.yosupo.jp/), [aizu judge](https://onlinejudge.u-aizu.ac.jp/courses/list)
