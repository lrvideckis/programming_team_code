/** @file */
#pragma once
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
template <typename T, typename F = function<T(const T&, const T&)>> struct deq {
    F op;
    vector<pair<T, T>> le, ri;
    /**
     * @param a_op associative operation
     * @time O(1)
     * @space O(1)
     */
    deq(const F& a_op) : op(a_op) {}
    /**
     * @returns deq[0] op deq[1] op ... op deq.back()
     * @time O(1)
     * @space O(1)
     */
    inline T query() const {
        assert(size());
        if (le.empty()) return ri.back().second;
        if (ri.empty()) return le.back().second;
        return op(le.back().second, ri.back().second);
    }
    /**
     * @returns size
     * @time O(1)
     * @space O(1)
     */
    inline int size() const {return ssize(le) + ssize(ri);}
    /**
     * @returns deq[0]
     * @time O(1)
     * @space O(1)
     */
    inline T front() const {
        assert(size());
        return le.empty() ? ri[0].first : le.back().first;
    }
    /**
     * @returns deq.back()
     * @time O(1)
     * @space O(1)
     */
    inline T back() const {
        assert(size());
        return ri.empty() ? le[0].first : ri.back().first;
    }
    /**
     * @param elem element to insert at beginning
     * @time O(1)
     * @space O(1)
     */
    inline void push_front(const T& elem) {
        le.emplace_back(elem, le.empty() ? elem : op(elem, le.back().second));
    }
    /**
     * @param elem element to insert at end
     * @time O(1)
     * @space O(1)
     */
    inline void push_back(const T& elem) {
        ri.emplace_back(elem, ri.empty() ? elem : op(ri.back().second, elem));
    }
    /**
     * remove deq[0]
     * @time O(1) ammortized
     * @space O(1) ammortized
     */
    inline void pop_front() {
        assert(size());
        if (le.empty()) {
            vector<T> arr(ssize(ri));
            transform(begin(ri), end(ri), begin(arr), [](const auto & x) {return x.first;});
            rebuild(arr, (ssize(arr) + 1) / 2);
        }
        assert(!le.empty());
        le.pop_back();
    }
    /**
     * remove deq.back()
     * @time O(1) ammortized
     * @space O(1) ammortized
     */
    inline void pop_back() {
        assert(size());
        if (ri.empty()) {
            vector<T> arr(ssize(le));
            transform(begin(le), end(le), rbegin(arr), [](const auto & x) {return x.first;});
            rebuild(arr, ssize(arr) / 2);
        }
        assert(!ri.empty());
        ri.pop_back();
    }
    inline void rebuild(const vector<T>& arr, int sz_le) {
        vector<T> presum(arr);
        partial_sum(begin(presum) + sz_le, end(presum), begin(presum) + sz_le, op);
        partial_sum(rend(presum) - sz_le, rend(presum), rend(presum) - sz_le, [&](const T & x, const T & y) {return op(y, x);});
        le.resize(sz_le);
        ri.resize(ssize(arr) - sz_le);
        transform(begin(arr), begin(arr) + sz_le, begin(presum), rbegin(le), [](const T & x, const T & y) {return pair(x, y);});
        transform(begin(arr) + sz_le, end(arr), begin(presum) + sz_le, begin(ri), [](const T & x, const T & y) {return pair(x, y);});
    }
};
