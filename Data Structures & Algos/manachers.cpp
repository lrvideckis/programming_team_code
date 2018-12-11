#include<bits/stdc++.h>
using namespace std;
#define int long long
typedef long long ll;

int cntPals(string &s) {
    string T = "";
    for(int i = 0; i < s.size(); ++i) {
        T += "#" + s.substr(i,1);
    }
    T += '#';
    vector<int> P(T.size(),0);
    int center = 0, boundary = 0, maxLen = 0, resCenter = 0, cnt = 0;
    for(int i = 1; i < T.size()-1; ++i) {
        int iMirror = 2 * center - i;
        P[i] = (boundary > i ? min(boundary - i, P[iMirror]) : 0);
        while(i-1-P[i] >= 0 && i+1+P[i] <= (int)T.size()-1 && T[i+1+P[i]] == T[i-1-P[i]])
            P[i]++;
        if(i + P[i] > boundary) {
            center = i;
            boundary = i+P[i];
        }
        cnt += (P[i]+1)/2;
    }
    return cnt;
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    string s = "fncksoaidnossssssssssofnadf";
    
    int naive = 0;
    for(int i = 0; i < s.size(); ++i) {
        string temp = "";
        for(int j = i; j < s.size(); ++j) {
            temp += s[j];
            bool good = true;
            for(int k = 0; k < temp.size(); ++k) {
                if(temp[k] != temp[temp.size()-k-1]) {
                    good = false;
                    break;
                }
            }
            naive += good;
        }
    }
    cout << "naive: " << naive << '\n';
    cout << "fast: " << cntPals(s) << '\n';
    return 0;
}



























