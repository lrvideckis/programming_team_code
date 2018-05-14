#include <bits/stdc++.h>
using namespace std;

vector<int> LIS(vector<int> &arr) {//longest non-decreasing sequence
    vector<int> longest(arr.size(),0);
    multiset<int> seq;
    for(int i = 0; i < arr.size(); ++i) {
        seq.insert(arr[i]);
        auto it = seq.upper_bound(arr[i]);
        if(it != seq.end()) seq.erase(it);
        longest[i] = seq.size();
    }
    return longest;
}

vector<int> LSIS(vector<int> &arr) {//longest strictly increasing sequence
    vector<int> longest(arr.size(),0);
    multiset<int> seq;
    for(int i = 0; i < arr.size(); ++i) {
        seq.insert(arr[i]);
        auto it = seq.lower_bound(arr[i]);
        it++;
        if(it != seq.end()) seq.erase(it);
        longest[i] = seq.size();
    }
    return longest;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    return 0;
}




















