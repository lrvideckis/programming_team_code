#define PROBLEM "https://judge.yosupo.jp/problem/predecessor_problem"
#include "../template.hpp"

#include "../../../library/data_structures/uncommon_data_structures/linear_rmq.hpp"

vector<int> convert_min(const string& s) {
    vector<int> arr(ssize(s), INT_MAX);
    for (int i = 0; i < ssize(s); i++)
        if (s[i] == '1') arr[i] = i;
    return arr;
}

vector<int> convert_max(const string& s) {
    vector<int> arr(ssize(s), -1);
    for (int i = 0; i < ssize(s); i++)
        if (s[i] == '1') arr[i] = i;
    return arr;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q;
    string s;
    cin >> n >> q >> s;
    linear_rmq<int> rmq_min_idx(convert_min(s), less()), rmq_max_idx(convert_max(s), greater());
    while (q--) {
        int type, k;
        cin >> type >> k;
        if (type == 0) {
            if (s[k] == '0') {
                s[k] = '1';
                rmq_min_idx.update(k, k);
                rmq_max_idx.update(k, k);
            }
        } else if (type == 1) {
            if (s[k] == '1') {
                s[k] = '0';
                rmq_min_idx.update(k, INT_MAX);
                rmq_max_idx.update(k, -1);
            }
        } else if (type == 2)
            cout << s[k] << '\n';
        else if (type == 3) {
            int idx = rmq_min_idx.query_idx(k, n);
            if (s[idx] == '0') cout << -1 << '\n';
            else cout << idx << '\n';
        } else {
            assert(type == 4);
            int idx = rmq_max_idx.query_idx(0, k + 1);
            if (s[idx] == '0') cout << -1 << '\n';
            else cout << idx << '\n';
        }
    }
    return 0;
}
