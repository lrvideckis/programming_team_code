#pragma once
#include "../../library/monotonic_stack_related/monotonic_range.hpp"
#include "../../library/data_structures/rmq.hpp"
void mono_st_asserts(const vector<int>& a) {
    vector<function<bool(int, int)>> compares;
    compares.push_back(less());
    compares.push_back(less_equal());
    compares.push_back(greater());
    compares.push_back(greater_equal());
    int n = ssize(a);
    for (auto cmp : compares) {
        RMQ rmq(a, [&](int x, int y) -> int { return cmp(x, y) ? x : y; });
        int iterations = 0;
        auto ri = mono_st(a, cmp), le = mono_range(ri);
        {
            vector old_way_le = mono_st<int>({rbegin(a), rend(a)}, [&](int x, int y) {return !cmp(y, x);});
            reverse(begin(old_way_le), end(old_way_le));
            transform(begin(old_way_le), end(old_way_le), begin(old_way_le), [&](int i) {return ssize(a) - i - 1;});
            assert(le == old_way_le);
        }
        for (int i = n - 1; i >= 0; i--) {
            assert(i < ri[i] && ri[i] <= n);
            assert(ri[i] == n || !cmp(a[i], a[ri[i]]));
            for (int j = i + 1; j != ri[i]; j = ri[j]) {
                // for all k in [j, ri[j]): cmp(a[i], a[k])
                // these ranges are disjoint, and union to [i + 1, ri[i])
                assert(j <= ri[i]);
                assert(cmp(a[i], a[j]));
                assert(cmp(a[i], a[ri[j] - 1]));
                assert(cmp(a[i], a[j + (ri[j] - j) / 2]));
                int range_op = rmq.query(j, ri[j]);
                assert(cmp(a[i], range_op));
                iterations++;
            }
        }
        // clear the stack
        for (int j = 0; j != n; j = ri[j]) iterations++;
        assert(iterations == n);
    }
}
