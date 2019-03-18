#include <bits/stdc++.h>
using namespace std;

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
        for(int i = 0; i < (int)arr.size(); ++i) sum += arr[i];
        vector<bool> tempRow(sum+1,false);
        vector<int> tempMinRow(sum+1,0);
        table.resize(arr.size()+1,tempRow);
        minSizeSet.resize(arr.size()+1,tempMinRow);
        for(int i = 0; i < (int)table.size(); ++i) table[i][0] = true;
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
                subset.push_back(arr[row-1]);
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    vector<int> a, b;
    int temp;
    cin >> temp;
    a.resize(temp);
    for(int i = 0; i < temp; ++i) cin >> a[i];
    cin >> temp;
    b.resize(temp);
    for(int i = 0; i < temp; ++i) cin >> b[i];
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    subsetSum subA(a), subB(b);
    int ans = 1e9, upper = min(subA.sum,subB.sum);
    for(int i = 1; i <= upper; ++i) {
        if(subA.query(i) && subB.query(i)) {
            ans = min(ans, (int)subA.minSize(i) + (int)subB.minSize(i));
        }
    }
    if(ans == (int)1e9) {
        cout << "impossible\n";
    } else {
        cout << ans << endl;
    }
    return 0;
}



















