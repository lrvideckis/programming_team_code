#include<bits/stdc++.h>
using namespace std;
#define int long long
typedef long long ll;

string cntPals(string &s) {
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
        if(P[i] > maxLen) {
            maxLen = P[i];
            resCenter = i;
        }
        cnt += (P[i]+1)/2;
    }
    return s.substr((resCenter - maxLen)/2, maxLen);
    //return cnt;//number of palindromes
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    string s = "fncksoaidnossssessssssofnadf";
    cout << "longest palindrome: " << cntPals(s) << '\n';
    
    s = "babcbabcbaccba";
    cout << "longest palindrome: " << cntPals(s) << '\n';
    
    s = "abaaba";
    cout << "longest palindrome: " << cntPals(s) << '\n';
    
    s = "abababa";
    cout << "longest palindrome: " << cntPals(s) << '\n';

    s = "abcbabcbabcba";
    cout << "longest palindrome: " << cntPals(s) << '\n';

    s = "forgeeksskeegfor";
    cout << "longest palindrome: " << cntPals(s) << '\n';

    s = "caba";
    cout << "longest palindrome: " << cntPals(s) << '\n';

    s = "abacdfgdcaba";
    cout << "longest palindrome: " << cntPals(s) << '\n';

    s = "abacdfgdcabba";
    cout << "longest palindrome: " << cntPals(s) << '\n';

    s = "abacdedcaba";
    cout << "longest palindrome: " << cntPals(s) << '\n';
  
    return 0;
}



























