#include <bits/stdc++.h>
using namespace std;


#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<class TI>
using indexed_set = tree<TI, null_type, less<TI>, rb_tree_tag, tree_order_statistics_node_update>;

//http://codeforces.com/blog/entry/11080
//http://codeforces.com/blog/entry/13279

struct rectangle {
    int length, width;
    bool operator<(const rectangle& rhs) {
        return (this->length*this->width < rhs.length*rhs.width);
    }
};

int main() {
    //usage:
    indexed_set<int> iSet;
    indexed_set<rectangle> iSet2;//just need to overload the < operator
    
    //functions: (insert, erase, find) have the same usage as regular sets:
    iSet.insert(1);
    iSet.insert(4);
    iSet.insert(6);
    iSet.insert(7);
    //1, 4, 6, 7
    
    iSet.erase(6);
    iSet.erase(10);
    //1, 4, 7
    
    cout << (iSet.find(4) != iSet.end()) << ' ';//true
    cout << (iSet.find(5) != iSet.end()) << '\n';//false
    
    /*
    order_of_key returns the index of item i. If i is not in the set, then
    order_of_key return the index of where i would go, if inserted.
    0-based indexing.
    */
    cout << iSet.order_of_key(1) << ' ';//0
    cout << iSet.order_of_key(7) << ' ';//2
    cout << iSet.order_of_key(5) << '\n';//2
    
    /*
    find_by_order returns an iterator to the i-th item
    find_by_order returns end if i is out of range
    */
    cout << *iSet.find_by_order(0) << ' ';//1
    cout << *iSet.find_by_order(1) << ' ';//4
    cout << *iSet.find_by_order(2) << ' ';//7
    
    cout << (iSet.end() == iSet.find_by_order(-1)) << ' ';//true
    cout << (iSet.end() == iSet.find_by_order(100)) << '\n';//true
    
    
    
    return 0;
}
