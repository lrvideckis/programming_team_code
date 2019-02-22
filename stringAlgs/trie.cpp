#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int K = 26;//character size

struct node {
    int next[K];
    bool leaf = 0;
    char pch;
    int p = -1;
    int id;
    node(int p = -1,char ch = '#'):p(p),pch(ch) {
        fill(next,next+K,-1);
    }
};

vector<node> t(1);//adj list

void add_string(string s, int id) {
    int c = 0;
    for(char ch: s){
        int v = ch-'a';
        if(t[c].next[v] == -1) {
            t[c].next[v] = t.size();
            t.emplace_back(c,ch);
        }
        c = t[c].next[v];
    }
    t[c].leaf = 1;
    t[c].id = id;
}

void remove_string(string s) {
    int c = 0;
    for(char ch: s){
        int v = ch-'a';
        if(t[c].next[v] == -1) {
            return;
        }
        c = t[c].next[v];
    }
    t[c].leaf = 0;
}

int find_string(string s) {
    int c = 0;
    for(char ch: s){
        int v = ch-'a';
        if(t[c].next[v] == -1) {
            return -1;
        }
        c = t[c].next[v];
    }
    if(!t[c].leaf) return -1;
    return t[c].id;
}

int32_t main() {

    vector<string> words = {"mom", "dad", "aj", "luke", "luck"};
    for(int i = 0; i < words.size(); ++i) {
        add_string(words[i], i);
    }
    
    cout<<"searching for words in/not in trie:\n";
    cout << "mom: " << find_string("mom") << '\n';
    cout << "mo: " << find_string("mo") << '\n';
    cout << "momo: " << find_string("momo") << '\n';
    cout << "lucky: " << find_string("lucky") << '\n';
    cout << "luck: " << find_string("luck") << '\n';
    cout << "luke: " << find_string("luke") << "\n\n";
    
    cout<<"erasing luke\n";
    remove_string("luke");
    cout << "luke: " << find_string("luke") << "\n\n";
    
    cout<<"inserting luke back\n";
    add_string("luke", 123);
    cout << "luke: " << find_string("luke") << '\n';
    cout << "lukey: " << find_string("lukey") << "\n\n";
     
    cout<<"trying to erase word not in list:\n";
    remove_string("lukey");
    cout << "lukey: " << find_string("lukey") << "\n\n";
    
    /*
    cout<<"printing all names in sorted order:\n";
    
    vector<string> temp = t.sort();
    for(string x : temp)cout<<x<<'\n';
    
    */
    return 0;
}






















