#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool table[2002][2002] = {0};
int arr[2002][2002] = {0}, cnt[2002][2002] = {0};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int rows, cols, n, d;
    cin >> rows >> cols >> n >> d;
    int i1, i2, j1, j2;
    while(n--) {
        cin >> i1 >> i2 >> j1 >> j2;
        for(int i = i1+1; i <= i2; ++i) {
            for(int j = j1+1; j <= j2; ++j) {
                table[i][j] = true;
            }
        }
    }
    for(int i = 1; i <= rows; ++i) {
        for(int j = 1; j <= cols; ++j) {
            arr[i][j] = 1 + arr[i][j-1];
            if(table[i][j]) arr[i][j] = 0;
        }
    }
    int tempRows;
    bool debug = true;
    for(int j = 1; j <= cols; ++j) {
        arr[rows+1][j] = 0;
        stack<pair<int, int> > st;
        st.push({0,0});
        int prevZero = 0;
        for(int i = 1; i <= rows+1; ++i) {
            pair<int, int> curr = {i, arr[i][j]};
            while(arr[i][j] < st.top().second) {
                curr = st.top();
                st.pop();
                cnt[i-curr.first][curr.second]++;
                cnt[i-curr.first][max(arr[i][j], st.top().second)]--;
            }
            st.push({curr.first, arr[i][j]});
        }
    }
    for(int j = 1; j <= cols; ++j) {
        for(int i = rows-1; i >= 1; --i) {
            cnt[i][j] += cnt[i+1][j];
        }
        for(int i = rows-1; i >= 1; --i) {
            cnt[i][j] += cnt[i+1][j];
        }
    }
    for(int i = 1; i <= rows; ++i) {
        for(int j = cols-1; j >= 1; --j) {
            cnt[i][j] += cnt[i][j+1];
        }
    }
    int i, j;
    while(d--) {
        cin >> i >> j;
        //cout << naive(i, j, rows, cols) << '\n';
        cout << cnt[i][j] << '\n';
    }
    return 0;
}
