#define PROBLEM "https://judge.yosupo.jp/problem/deque_operate_all_composite"
#include "../template.hpp"

#include "../../../library/contest/random.hpp"
#include "../../../library/data_structures/uncommon/deque_with_op.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    const int mod = 998'244'353;
    int q;
    cin >> q;
    using line = pair<int, int>;
    //f1 = begin, f2 = second after begin
    //we want op(f1, f2) = the function f2(f1(x))
    deq dq(vector<line>(), [](const line & i, const line & j) -> line {
        return pair(1LL * i.first * j.first % mod,
                    (1LL * j.first * i.second + j.second) % mod);
    });
    deque<line> stl_dq;
    while (q--) {
        int type;
        cin >> type;
        if (type == 0) {
            int a, b;
            cin >> a >> b;
            dq.push_front(pair(a, b));
            stl_dq.emplace_front(a, b);
        } else if (type == 1) {
            int a, b;
            cin >> a >> b;
            dq.push_back(pair(a, b));
            stl_dq.emplace_back(a, b);
        } else if (type == 2) {
            dq.pop_front();
            stl_dq.pop_front();
        } else if (type == 3) {
            dq.pop_back();
            stl_dq.pop_back();
        } else {
            assert(type == 4);
            int x;
            cin >> x;
            if (dq.size() == 0)
                cout << x << '\n';
            else {
                line curr = dq.query();
                cout << (1LL * curr.first * x + curr.second) % mod << '\n';
            }
        }
        auto curr_1 = dq.size();
        assert(ssize(stl_dq) == curr_1);
        if (dq.size()) {
            auto curr_2 = stl_dq.front();
            auto curr_res_1 = dq.front();
            assert(curr_2 == curr_res_1);
            auto curr_3 = stl_dq.back();
            auto curr_res_2 = dq.back();
            assert(curr_3 == curr_res_2);
            for (int index_tests = 10; index_tests--;) {
                int idx = get_rand<int>(0, dq.size() - 1);
                assert(stl_dq[idx] == dq[idx]);
            }
        }
    }
    return 0;
}
