//status: not tested

//place these includes *before* the `#define int long long` else compile error
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

//BST with extra functions https://codeforces.com/blog/entry/11080
//order_of_key - # of elements *strictly* less than given element
//find_by_order - find kth largest element, k is 0 based so find_by_order(0) returns min element
template<class T>
using indexed_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
//example initialization:
indexed_set<pair<long long, int>> is;


//hash table (apparently faster than unordered_map): https://codeforces.com/blog/entry/60737
//example initialization:
gp_hash_table<string, long long> ht;
