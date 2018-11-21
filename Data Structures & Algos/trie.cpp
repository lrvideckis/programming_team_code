#include <bits/stdc++.h>
using namespace std;

struct trie {//only lowercase letters for all words
private:
    struct node {
        bool isWord;
        vector<node*> children;
        node() {
            isWord=false;
            children.resize(26,nullptr);
        }
    };
    node *root;
    //for easy memory cleanup
    vector<node*> allNodes;
public:
    trie() {
        root = new node();
        allNodes.push_back(root);
    }
    trie(vector<string> &arr) {//initialize a trie and insert all words in arr
        root = new node();
        allNodes.push_back(root);
        for(string x : arr) insert(x);
    }
    ~trie() {
        for(node* x : allNodes) delete x;
    }
    void insert(string word) {
        node *curr = root;
        for(char x : word) {
            if(curr->children[x-'a'] == nullptr) {
                curr->children[x-'a'] = new node();
                allNodes.push_back(curr->children[x-'a']);
            }
            curr = curr->children[x-'a'];
        }
        curr->isWord = true;
    }
    bool find(string word) {
        node* curr = root;
        for(char x : word) {
            if(curr->children[x-'a'] == nullptr) return false;
            curr = curr->children[x-'a'];
        }
        return curr->isWord;
    }
    void erase(string word) {
        node* curr = root;
        for(char x : word) {
            if(curr->children[x-'a'] == nullptr) return;
            curr = curr->children[x-'a'];
        }
        curr->isWord = false;
    }
    void preorder(node* curr, vector<string> &arr, string &word) {
        if(curr->isWord) arr.push_back(word);
        for(int i = 0; i < 26; ++i) {
            if(curr->children[i] != nullptr) {
                word += i+'a';
                preorder(curr->children[i], arr, word);
                word.pop_back();
            }
        }
    }
    vector<string> sort() {//Pre-order traversal to get all words in sorted order
        vector<string> arr;
        string word = "";
        preorder(root, arr, word);
        return arr;
    }
};


const int Max = 1e5+100;
const int root = 1;
set<int> adj[Max];
vector<int> children[Max];
int cnt[Max];

int32_t main() {
    int n;
    cin >> n;
    string s;
    int nextID = 2;
    for(int i = 0; i < n; ++i) {
        cin >> s;
        int curr = root;
        for(int j = 0; j < (int)s.size(); ++j) {
            if(children[curr].empty()) children[curr].resize(26,-1);
            if(children[curr][s[j]-'a'] == -1) {
                children[curr][s[j]-'a'] = nextID++;
            }
            int next = children[curr][s[j]-'a'];
            adj[curr].insert(next);
            adj[next].insert(curr);
            if(j+1 == (int)s.size()) {
                cnt[next]++;
            }
            curr = next;
        }
    }




    vector<string> words = {"mom", "dad", "aj", "luke", "luck"};
    trie t(words);
    
    cout<<"searching for words in/not in trie:\n";
    cout << "mom: " << t.find("mom") << '\n';
    cout << "mo: " << t.find("mo") << '\n';
    cout << "momo: " << t.find("momo") << '\n';
    cout << "lucky: " << t.find("lucky") << '\n';
    cout << "luck: " << t.find("luck") << '\n';
    cout << "luck: " << t.find("luck") << '\n';
    cout << "luke: " << t.find("luke") << "\n\n";
    
    cout<<"erasing luke\n";
    t.erase("luke");
    cout << "luke: " << t.find("luke") << "\n\n";
    
    cout<<"inserting luke back\n";
    t.insert("luke");
    cout << "luke: " << t.find("luke") << '\n';
    cout << "lukey: " << t.find("lukey") << "\n\n";
     
    cout<<"trying to erase word not in list:\n";
    t.erase("lukey");
    cout << "lukey: " << t.find("lukey") << "\n\n";
    
    cout<<"printing all names in sorted order:\n";
    
    vector<string> temp = t.sort();
    for(string x : temp)cout<<x<<'\n';
    
    return 0;
}






















