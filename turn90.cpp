/*
abc     mjgda
def ->  nkheb
ghi     olifc
jkl
mno

***has to be a rectangular 2D array***
*/
vector<string> turn90(vector<string> arr) {
    vector<string> ans(arr[0].size());
    rep(j, arr[0].size()) {
        for(int i = arr.size()-1; i >= 0; --i) {
            ans[j].pb(arr[i][j]);
        }
    }
    return ans;
}
