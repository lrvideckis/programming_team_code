/** @file */
#pragma once
/**
 * deque with query for operation of the deque
 * @code{.cpp}
 *     //deque with query for: get min and # of mins in deque
 *     vector<pair<long long, int>> arr;//initialize arr[i].second = 1
 *     ...
 *     deq<pair<long long, int>> dq(arr, [](const auto& x, const auto& y) {
 *         if (x.first == y.first) return pair(x.first, x.second + y.second);
 *         return min(x, y);
 *     });
 * @endcode
 */
template <class T, class F = function<T(T, T)>> struct deq {
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
     * @param arr initial array: arr[0] is front, arr.back() is back
     * @param a_op associative operation
     * @time O(1)
     * @space O(1)
     */
    deq(const vector<T>& arr, F a_op) : op(a_op) {rebuild(arr, ssize(arr) / 2);}
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
        return (le.empty() ? ri[0] : le.back()).first;
    }
    /**
     * @returns deq.back()
     * @time O(1)
     * @space O(1)
     */
    inline T back() const {
        assert(size());
        return (ri.empty() ? le[0] : ri.back()).first;
    }
    /**
     * @param i index
     * @returns deq[i]
     * @time O(1)
     * @space O(1)
     */
    inline T operator[](int i) const {
        assert(0 <= i && i < size());
        return (i < ssize(le) ? le[ssize(le) - i - 1] : ri[i - ssize(le)]).first;
    }
    /**
     * @param elem element to insert at beginning
     * @time O(1)
     * @space O(1)
     */
    inline void push_front(T elem) {
        le.emplace_back(elem, le.empty() ? elem : op(elem, le.back().second));
    }
    /**
     * @param elem element to insert at end
     * @time O(1)
     * @space O(1)
     */
    inline void push_back(T elem) {
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
        vector<T> presum(ssize(arr));
        partial_sum(rend(arr) - sz_le, rend(arr), rend(presum) - sz_le, [&](T x, T y) {return op(y, x);});
        partial_sum(begin(arr) + sz_le, end(arr), begin(presum) + sz_le, op);
        le.resize(sz_le);
        ri.resize(ssize(arr) - sz_le);
        transform(begin(arr), begin(arr) + sz_le, begin(presum), rbegin(le), [](T x, T y) {return pair(x, y);});
        transform(begin(arr) + sz_le, end(arr), begin(presum) + sz_le, begin(ri), [](T x, T y) {return pair(x, y);});
    }
};
