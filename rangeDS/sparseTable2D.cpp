//***zero based indexing
int table[11][1010][11][1010],logTwo[1010];
struct sparseTable2D {
    int n, m;
    sparseTable2D(const vector<vector<int>> &Matrix) {
        n = Matrix.size();
        m = Matrix[0].size();
        logTwo[0] = -1;
        for(int i = 1; i <= max(n,m); ++i) {
            logTwo[i] = 1 + logTwo[i/2];
        }
        for(int ir=0; ir<n; ++ir) {
            for(int ic=0; ic<m; ++ic)
                table[0][ir][0][ic] = Matrix[ir][ic];
            for(int jc=1; jc<=logTwo[m]; ++jc)
                for(int ic=0; ic+(1<<(jc-1))<m; ++ic)
                    table[0][ir][jc][ic] = min(table[0][ir][jc-1][ic], table[0][ir][jc-1][ic+(1<<(jc-1))]);
        }
        for(int jr=1; jr<=logTwo[n]; ++jr)
            for(int ir=0; ir<n; ++ir)
                for(int jc=0; jc<=logTwo[m]; ++jc)
                    for(int ic=0; ic<m; ++ic)
                        table[jr][ir][jc][ic] = min(table[jr-1][ir][jc][ic], table[jr-1][ir+(1<<(jr-1))][jc][ic]);
    }
    int queryMin(int x1, int y1, int x2, int y2){
        int kx = logTwo[x2-x1+1];
        int ky = logTwo[y2-y1+1];
        int min_R1 = min(table[kx][x1][ky][y1], table[kx][x1][ky][y2+1-(1<<ky)]);
        int min_R2 = min(table[kx][x2+1-(1<<kx)][ky][y1], table[kx][x2+1-(1<<kx)][ky][y2+1-(1<<ky)]);
        return min(min_R1, min_R2);
    }
};
