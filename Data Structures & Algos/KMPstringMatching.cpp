#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct KMP_Match {
    vector<int> T;
    string pat;
    KMP_Match() {};
    KMP_Match(string pattern) : pat(pattern) {this->buildTable(pat);};
    void buildTable(string pattern) {
        pat = pattern;
        T.clear();
        T.resize(pat.length()+1);       
        int i = 0, j = -1;
        T[i] = j;
        while(i < pat.size()) {
            while(j >= 0 && pat[i] != pat[j]) j = T[j];
            i++, j++;
            T[i] = j;
        }
    }
    vector<int> find(string txt, bool all = true) {
        int m = 0, i = 0;
        vector<int> matches;
        while(m + i < txt.length()) {
            if(pat[i] == txt[m+i]) {
                if(i == pat.length()-1) {
                    matches.push_back(m);
                    if(!all) return matches;
                    m = m + i - T[i];
                    i = T[i];
                }   
                i++;
            } else {
                if(T[i] != -1) {
                    m = m + i - T[i];
                    i = T[i];
                } else {
                    i = 0;
                    m++;
                }
            }
        }
        return matches;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    string a, b;
    KMP_Match kmp(a);
    vector<int> matches = kmp.find(b);
    return 0;
}






