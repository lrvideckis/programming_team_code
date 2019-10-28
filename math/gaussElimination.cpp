const double eps = 0.00000001;
int Rank;
double Det;
void gauss(vector<vector<double>> &a) {
    int n = a.size();
    int m = a[0].size();//possible RTE here
    Det = 1.0, Rank = 0;
    vector<int> where(max(n, m)+1, -1);
    for(int col = 0, row = 0; col < m && row < n; ++col) {
        int sel = row;
        for(int i = row+1; i < n; ++i)
            if(abs(a[i][col]) > abs(a[sel][col])) sel = i;
        if(abs(a[sel][col]) < eps) { Det = 0.0; continue; }
        for(int j = 0; j < m; ++j) swap(a[sel][j], a[row][j]);
        if(row != sel) Det = -Det;
        Det = Det * a[row][col];
        where[col] = row;
        double s = (1.0 / a[row][col]);
        for(int j = 0; j < m; ++j) a[row][j] = a[row][j] * s;
        for(int i = 0; i < n; ++i) if (i != row && abs(a[i][col]) > eps) {
            double t = a[i][col];
            for(int j = 0; j < m; ++j) a[i][j] = a[i][j] - (a[row][j] * t);
        }
        ++row, ++Rank;
    }
}
