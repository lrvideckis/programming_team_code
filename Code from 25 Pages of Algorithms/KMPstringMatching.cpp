#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct KMP_Match {
    vector<int> T;      //prefix table for KMP algorithm
    string pat;         //pattern for current prefix table and for searching

    //constructors: empty and with pattern, which builds prefix table
    KMP_Match() {};
    KMP_Match(string pattern) : pat(pattern) { this->buildTable(pat); };

    //build prefix table for KMP algorithm
    void buildTable(string pattern) {
        pat = pattern;
        T.clear();
        T.resize(pat.length()+1);       
        int i = 0, j = -1;
        T[i] = j;
        while (i < pat.size()) {
            while (j >= 0 && pat[i] != pat[j]) j = T[j];
            i++, j++;
            T[i] = j;
        }
    }

    //returns list of all match positions of pat in txt; if no matches, returns empty vector
    //if all = false, returns vector with single element, position of first match
    vector<int> find(string txt, bool all = true)
    {
        int m = 0, i = 0;   //start of current match in txt, position in pat
        vector<int> matches;        //list of matches
    
        while (m + i < txt.length()) {      //search to end of txt
            if (pat[i] == txt[m+i]) {       //characters match              
                if (i == pat.length()-1) {  //end of pattern,  store location of match
                    matches.push_back(m);
                    if (!all) return matches;   //only want first match, return
                    m = m + i - T[i];           //move forward to continue searching
                    i = T[i];
                }   
                i++;        //move to next character of pat         
            }               
            else {                  //characters do not match, keep searching               
                if (T[i] != -1) {   //valid border, skip ahead
                    m = m + i - T[i];   //current pos + length of match - known matched
                    i = T[i];           //start just after known matched
                }               
                else {      //no valid border, try next character
                    i = 0;
                    m++;
                }
            }       
        }       
        return matches;   //return list of matches
    }
};

int main()
{
    /*string a, b;
    KMP_Match kmp(a);
    vector<int> matches = kmp.find(b);*/
    return 0;
}
