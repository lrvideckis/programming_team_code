/** @file */
#pragma once
/**
 * @see https://codeforces.com/blog/entry/78931 https://codeforces.com/blog/entry/92310
 * @code{.cpp}
 *     vector<long long> arr;
 *     linear_rmq rmq(arr, less<long long>());//minimum query
 *     linear_rmq rmq(arr, greater<long long>());//maximum query
 * @endcode
 */
template <class T, class F> struct linear_rmq {
    int n;
    vector<T> arr;
    F less;
    /**
     * on the level'th level, blocks are:
     * 0-th block: [0*64^level, 1*64^level)
     * 1-st block: [1*64^level, 2*64^level)
     * 2-nd block: [2*64^level, 3*64^level)
     * ...
     * mask[level][i] = min-monotonic stack over blocks [i, i+64)
     * idx[level][i] = array idx of minimum over all values in blocks [i, i+64)
     * @{
     */
    vector<vector<uint64_t>> mask;
    vector<vector<int>> idx;
    /** @} */
    /**
     * @param a_arr an array
     * @param a_less transitive compare operator
     * @time O(n)
     * @space `arr`, `mask`, and `idx` vectors are all O(n)
     */
    linear_rmq(const vector<T>& a_arr, F a_less) : n(int(ssize(a_arr))), arr(a_arr), less(a_less) {
        for (int sz = n; sz >= 2; sz = ((sz + 63) >> 6)) {
            int level = int(ssize(idx));
            mask.emplace_back(sz + 1);
            idx.emplace_back(sz);
            calc(level, 0, sz);
        }
    }
    void calc(int level, int le, int ri) {
        for (int i = ri - 1; i >= le; i--) {
            uint64_t st = mask[level][i + 1];
            T curr = arr[blk(level, i)];
            while (st && less(curr, arr[blk(level, i + 1 + __builtin_ctzll(st))])) st &= st - 1;
            mask[level][i] = st = ((st << 1) | 1);
            idx[level][i] = blk(level, i + int(__lg(st)));
        }
    }
    /**
     * @param level,i defines a block, corresponding to arr[i*64^level, (i+1)*64^level)
     * @returns array index of minimum in block
     */
    int blk(int level, int i) const {
        return level ? idx[level - 1][i << 6] : i;
    }
    int mn(int le, int ri) const {
        return less(arr[le], arr[ri]) ? le : ri;
    }
    /**
     * @param le,ri defines range [le, ri)
     * @returns index of minimum in range
     * @time O(log(n) / log(log(n))), practically if n <= 2^24 then ssize(mask) <= 4
     * @space O(1)
     */
    int query_idx(int le, int ri) const {
        assert(0 <= le && le < ri && ri <= n);
        int res = le;
        for (int level = 0; le < ri && level < ssize(mask); level++, le = (le >> 6) + 1, ri = ((ri - 1) >> 6)) {
            if (ri - le < 64) {
                int x = 64 - (ri - le);
                return mn(res, blk(level, le + int(__lg(mask[level][le] << x)) - x));
            }
            res = mn(res, mn(idx[level][le], idx[level][ri - 64]));
        }
        return res;
    }
    /**
     * @param le,ri defines range [le, ri)
     * @returns minimum in range
     * @time O(log(n) / log(log(n)))
     * @space O(1)
     */
    int query(int le, int ri) const {
        return arr[query_idx(le, ri)];
    }
    /**
     * @param pos index to update
     * @param val new value
     * @time O((log(n)^2) / log(log(n)))
     * @space O(1)
     */
    void update(int pos, T val) {
        assert(0 <= pos && pos < n);
        arr[pos] = val;
        for (int level = 0; level < ssize(mask); level++, pos >>= 6)
            calc(level, max(0, pos - 63), pos + 1);
    }
};
