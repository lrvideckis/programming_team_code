## Out of scope

- [Geometry](https://github.com/kth-competitive-programming/kactl/tree/main/content/geometry)

[![](https://github.com/lrvideckis/programming_team_code/blob/master/tests/scripts/geometry_bad.png)](https://codeforces.com/blog/entry/52341?#comment-364050)
- [Fast Fourier transform](https://github.com/kth-competitive-programming/kactl/blob/main/content/numerical/FastFourierTransform.h)
- [2-sat](https://github.com/kth-competitive-programming/kactl/blob/main/content/graph/2sat.h)
- [Chinese Remainder Theorem](https://github.com/kth-competitive-programming/kactl/blob/main/content/number-theory/CRT.h)
- [Convex Hull Trick](https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/LineContainer.h)
- [Miller Rabin](https://github.com/kth-competitive-programming/kactl/blob/main/content/number-theory/MillerRabin.h)
- [Z function](https://github.com/kth-competitive-programming/kactl/blob/main/content/strings/Zfunc.h)
- [Manacher's](https://github.com/kth-competitive-programming/kactl/blob/main/content/strings/Manacher.h)
- [Sqrt decomposition](https://github.com/nealwu/competitive-programming/blob/master/sqrt/search_buckets.cc) (search buckets)
- [fast IO](https://github.com/nealwu/competitive-programming/blob/master/io/io.cc) - I've never TLE'd specifically from IO slowness while using both  `cin.tie(0)->sync_with_stdio(0);` and `'\n'`
- [Interval container](https://github.com/kth-competitive-programming/kactl/blob/main/content/various/IntervalContainer.h)
- 2D data structures (like [seg tree](https://github.com/ShahjalalShohag/code-library/blob/master/Data%20Structures/Segment%20Tree%202D%20Dynamic.cpp), [sparse table](https://codeforces.com/blog/entry/45485) etc)
- [queue with get max](https://github.com/ucf-programming-team/hackpack-cpp/blob/lightseba-general-changes/content/data-structures/MonotonicQueue.h)
- [seg tree beats](https://codeforces.com/blog/entry/57319)
- [polynomial stuff](https://cp-algorithms.com/algebra/polynomial.html)
- [Disjoint set](https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/UnionFind.h)
- [DSU with rollback](https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/UnionFindRollback.h)
- [string hashing](https://github.com/kth-competitive-programming/kactl/blob/main/content/strings/Hashing.h)
- [string rotational equivalence](https://github.com/kth-competitive-programming/kactl/blob/main/content/strings/MinRotation.h)
- [Hilbert Mo](https://github.com/ucf-programming-team/hackpack-cpp/blob/lightseba-general-changes/content/misc/HilbertMos.h)
- [Non-lazy seg tree](https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/SegmentTree.h)
- [Floyd Warshall](https://github.com/kth-competitive-programming/kactl/blob/main/content/graph/FloydWarshall.h)
- [Suffix Array and LCP Array](https://github.com/atcoder/ac-library/blob/master/atcoder/string.hpp)
- [Matrix Operations](https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/Matrix.h)

## Things to consider when adding a new alg to the library
- How often have you seen it
- No good implementation elsewhere (usually kactl)
- How hard to modify existing library code
- Easily testable (preferably there is a problem to test, instead of [custom stress tests](https://github.com/lrvideckis/programming_team_code/tree/master/tests/oj_tests/pseudo_tests))
