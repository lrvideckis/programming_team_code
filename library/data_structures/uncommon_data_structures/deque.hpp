/** @file */
#pragma once
/**
 * deque with query for operation of the deque
 */
template <typename T, typename F = function<T(const T&, const T&)>> struct deq {
    F op;
    /**
     * @see https://github.com/suisen-cp/cp-library-cpp /blob/main/library/datastructure/deque_aggregation.hpp
     * simulate a deque with 2 stacks:
     * `le`, `ri` are stacks of { value, sum }
     *     accumulate
     *    <-----------  -------> fold values from inside
     *   (     le     ][  ri    )
     * @{
     */
    vector<pair<T, T>> le, ri;
    /** @} */
    /**
     * @param a_op associative operation
     * @time O(1)
     * @space O(1)
     */
    deq(F a_op) : op(a_op) {}
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
        partial_sum(rend(presum) - sz_le, rend(presum), rend(presum) - sz_le, [&](const T & x, const T & y) {return op(y, x);});
        partial_sum(begin(presum) + sz_le, end(presum), begin(presum) + sz_le, op);
        le.resize(sz_le);
        ri.resize(ssize(arr) - sz_le);
        transform(begin(arr), begin(arr) + sz_le, begin(presum), rbegin(le), [](const T & x, const T & y) {return pair(x, y);});
        transform(begin(arr) + sz_le, end(arr), begin(presum) + sz_le, begin(ri), [](const T & x, const T & y) {return pair(x, y);});
    }
};
