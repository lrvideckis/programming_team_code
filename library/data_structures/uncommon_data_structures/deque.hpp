/** @file */
#pragma once
template <typename T, typename F = function<T(const T&, const T&)>> struct deq {
    F op;
    vector<pair<T, T>> le, ri;
    deq(const F& a_op) : op(a_op) {}
    inline T query() const {
        assert(size());
        if(le.empty()) return ri.back().second;
        if(ri.empty()) return le.back().second;
        return op(le.back().second, ri.back().second);
    }
    inline int size() const {return ssize(le) + ssize(ri);}
    inline T front() const {return le.empty() ? ri[0].first : le.back().first;}
    inline T back() const {return ri.empty() ? le[0].first : ri.back().first;}
    inline void push_front(const T& elem) {
        le.emplace_back(elem, le.empty() ? elem : op(elem, le.back().second));
    }
    inline void push_back(const T& elem) {
        ri.emplace_back(elem, ri.empty() ? elem : op(ri.back().second, elem));
    }
    inline void pop_front() {
        assert(size());
        if(le.empty()) {
            vector<T> arr(ssize(ri));
            transform(begin(ri), end(ri), begin(arr), [](pair<T,T> x) {return x.first;});
            rebuild(arr, (ssize(arr)+1)/2);
        }
        assert(!le.empty());
        le.pop_back();
    }
    inline void pop_back() {
        assert(size());
        if(ri.empty()) {
            vector<T> arr(ssize(le));
            transform(begin(le), end(le), rbegin(arr), [](pair<T,T> x) {return x.first;});
            rebuild(arr, ssize(arr)/2);
        }
        assert(!ri.empty());
        ri.pop_back();
    }
    inline void rebuild(const vector<T>& arr, int sz_le) {
        vector<T> presum(arr);
        partial_sum(begin(presum) + sz_le, end(presum), begin(presum) + sz_le, op);
        partial_sum(rend(presum) - sz_le, rend(presum), rend(presum) - sz_le, [&](T x, T y) {return op(y, x);});
        le.resize(sz_le);
        ri.resize(ssize(arr) - sz_le);
        transform(begin(arr), begin(arr) + sz_le, begin(presum), rbegin(le), [](T x, T y) {return pair(x, y);});
        transform(begin(arr) + sz_le, end(arr), begin(presum) + sz_le, begin(ri), [](T x, T y) {return pair(x, y);});
    }
};
