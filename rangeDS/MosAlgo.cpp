#include <bits/stdc++.h>
using namespace std;

const int Max = 1e6+2;
int block, answer[Max], answerToQuery;

struct query {
    int l, r, index;
};

bool cmp(query x, query y) {
    if(x.l/block == y.l/block) return x.r < y.r;
    return x.l < y.l;
}
void add(int pos) {
}
void remove(int pos) {
}

int main() {
    int q;
    cin >> q;
    vector<query> queries(q);
    for(int i = 0; i < q; ++i) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].index = i;
        answer[i] = 0;
    }
    sort(queries.begin(), queries.end(), cmp);
    int left = 0, right = 0;//store inclusive ranges, start at [0,0]
    add(0);
    answerToQuery = 0;
    for(auto &q : queries) {
        while(left > q.l) {
            left--;
            add(left);
        }
        while(right < q.r) {
            right++;
            add(right);
        }
        while(left < q.l) {
            remove(left);
            left++;
        }
        while(right > q.r) {
            remove(right);
            right--;
        }
        answer[q.index] = answerToQuery;
    }
    for(int i = 0; i < q; ++i) cout << answer[i] << '\n';
    return 0;
}
