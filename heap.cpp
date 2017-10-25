#define _USE_MATH_DEFINES//M_PI
#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
#define int long long
#define ll long long
#define ld long double
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define uni(x) (x).erase(unique(all(x)), (x).end());
#define rep(i, n) for (int i = 0; i < (int)(n); ++i)
#define rep1(i, n) for (int i = 1; i <= (int)(n); ++i)
const ll infll = powl(2, 62)-1;
const int mod = pow(10, 9) + 7;

bool minHeap(int a, int b) {return a > b;}//flip this for max heap
class heap {
    vector<int> arr;
    public:
    heap(){}
    heap(vector<int> &arr) {this->arr = arr; make_heap(all(this->arr), minHeap);}
    void push(int n) {this->arr.pb(n); push_heap(all(this->arr), minHeap);}
    void pop() {pop_heap(all(this->arr), minHeap); this->arr.pop_back();}
    int top() {return (this->arr.size()?this->arr[0]:infll);}
    bool empty() {return !(bool)(this->arr.size());}
    void clear() {this->arr.clear();}
    int size() {return this->arr.size();}
    vector<int>* sort() {sort_heap(all(arr)); return &arr;}
};

int32_t main() {
    //example usage
    vector<int> temp = {2, 5, 3, 1, 4};
    heap hp(temp);
    while(!hp.empty()) {
        cout << hp.top() << endl;
        hp.pop();
    }
    cout << "size: " << hp.size() << endl;
    rep(i, 5) {
        int temp = 2*i*i-5*i+7;
        cout << "adding: " << temp << endl;
        hp.push(temp);
    }
    while(!hp.empty()) {
        cout << hp.top() << endl;
        hp.pop();
    }
    
    return 0;
}















