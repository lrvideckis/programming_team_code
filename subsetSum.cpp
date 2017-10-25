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

/*inspired by problem "Nine Packs" on Kattis, this code is my solution to the problem

this struct takes in an array of integers, and answers queries of the form:
is there a subset of the initial array with sum equal to target (partition problem)

let n = array size, sum = sum of elements in array

time to calculate table: O(n * sum)
space of table: O(n * sum)
time of queries: O(1)
time of minSet queries: O(1)
time to get the set of integers with sum == tgt: O(n)
*/
struct subsetSum {
    vector<int> arr;
    vector<vector<bool> > table;
    vector<vector<int> > minSizeSet;
    int sum;
    subsetSum(vector<int> &arr) {
        this->arr = arr;
        sum = 0;
        rep(i,arr.size()) sum += arr[i];
        vector<bool> tempRow(sum+1,false);
        vector<int> tempMinRow(sum+1,0);
        table.resize(arr.size()+1,tempRow);
        minSizeSet.resize(arr.size()+1,tempMinRow);
        rep(i,table.size()) table[i][0] = true;
        for(int i = 1; i <= arr.size(); i++) {
            for (int j = 1; j <= sum; j++) {
                if (j - arr[i-1] >= 0) {
                    table[i][j] = table[i-1][j] || table[i-1][j-arr[i-1]];
                    if(table[i-1][j-arr[i-1]] && table[i-1][j]) {
                        minSizeSet[i][j] = min(minSizeSet[i-1][j], 1+minSizeSet[i-1][j-arr[i-1]]);
                    } else if(table[i-1][j]) {
                        minSizeSet[i][j] = minSizeSet[i-1][j];
                    } else if(table[i-1][j-arr[i-1]]) {
                        minSizeSet[i][j] = 1+minSizeSet[i-1][j-arr[i-1]];
                    }
                } else {
                    table[i][j] = table[i-1][j];
                    minSizeSet[i][j] = minSizeSet[i-1][j];
                }
            }
        }
    }
    //returns true iff there is a subset in arr with sum==tgt
    bool query(int tgt) {
        if(tgt < 0 || tgt > sum) return false;
        return table[arr.size()][tgt];
    }
    //returns the smallest size of a set with sum equal to tgt
    //returns -1 if set doesnt exist
    int minSize(int tgt) {
        if(!query(tgt)) return -1;
        return minSizeSet[arr.size()][tgt];
    }
    //returns subset of numbers with sum equal to tgt
    //returns empty set in the case where there is no subset with sum==tgt
    vector<int> getSet(int tgt) {
        vector<int> subset;
        if(!query(tgt)) return subset;
        int row = arr.size(), col = tgt;
        while(col > 0 && row > 0) {
            if(col-arr[row-1] >= 0 && table[row-1][col-arr[row-1]]) {
                subset.pb(arr[row-1]);
                col -= arr[row-1];
            }
            row--;
        }
        return subset;
    }
    //returns true iff there are 2 disjoint subsets whose union is the whole set which have an equal sum
    bool partition() {
        if (sum % 2 != 0) return false;
        return table[arr.size()][sum/2];
    }
};

int32_t main() {//ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    vector<int> a, b;
    int temp;
    cin >> temp;
    a.resize(temp);
    rep(i,temp) cin >> a[i];
    cin >> temp;
    b.resize(temp);
    rep(i,temp) cin >> b[i];
    sort(all(a));
    sort(all(b));
    subsetSum subA(a), subB(b);
    int ans = infll, upper = min(subA.sum,subB.sum);
    rep1(i,upper) {
        if(subA.query(i) && subB.query(i)) {
            ans = min(ans, (int)subA.minSize(i) + (int)subB.minSize(i));
        }
    }
    if(ans == infll) {
        cout << "impossible\n";
    } else {
        cout << ans << endl;
    }
    return 0;
}



















