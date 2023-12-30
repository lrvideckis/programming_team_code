## explanation of the greedy

### the problem

`3 * (sum + sub_sz[v]) <= 2 * (siz - 1)` is the greedy from https://codeforces.com/blog/entry/104997 but for example once the first set has more than half the edges (e.g. `2 * sum >= siz - 1`) we potentially can still add to it, making the sets more unbalanced.

### the fix

define balance = `abs(size_of_edge_set_1 - size_of_edge_set_2)`

- before adding `sub_sz[v]`, balance = `abs(sum - (siz - 1 - sum))`
- after adding `sub_sz[v]`, balance = `abs(sum + sub_sz[v] - (siz - 1 - sum - sub_sz[v]))`

we want to add `v` to the edge set only when that decreases the balance.
