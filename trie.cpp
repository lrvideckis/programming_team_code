#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
#define int long long
#define ll long long
#define ld long double
#define pb push_back
#define mp make_pair
#define endl '\n'
#define D(x) cout<<#x<<" -> "<<x<<'\n'
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define uni(x) (x).erase(unique(all(x)), (x).end());
#define rep(i, n) for (int i = 0; i < (int)(n); ++i)
#define rep1(i, n) for (int i = 1; i <= (int)(n); ++i)
const ll infll = powl(2, 62)-1;
const ld pi = 4.0*atanl(1.0);
const int mod = powl(10, 9) + 7;

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
        allNodes.pb(root);
    }
    trie(vector<string> &arr) {//initialize a trie and insert all words in arr
        root = new node();
        allNodes.pb(root);
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
                allNodes.pb(curr->children[x-'a']);
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
        if(curr->isWord) arr.pb(word);
        rep(i,26) {
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

int32_t main() {
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






















