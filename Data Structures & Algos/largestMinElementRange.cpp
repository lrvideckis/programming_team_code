#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> arr(n), lefts(n), rights(n);
    for(int &x : arr) cin >> x;
    stack<int> positions;
    for(int i = 0; i < n; ++i) {
        while(!positions.empty() && arr[positions.top()] >= arr[i]) positions.pop();
        if(positions.empty()) {
            lefts[i] = -1;
        } else {
            lefts[i] = positions.top();
        }
        positions.push(i);
    }
    while(!positions.empty()) positions.pop();
    for(int i = n-1; i >= 0; --i) {
        while(!positions.empty() && arr[positions.top()] >= arr[i]) positions.pop();
        if(positions.empty()) {
            rights[i] = n;
        } else {
            rights[i] = positions.top();
        }
        positions.push(i);
    }
    return 0;
}
