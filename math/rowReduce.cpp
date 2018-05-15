#include <bits/stdc++.h>
using namespace std;

void reduce(pair<int, int> &x) {
    int temp = __gcd(x.first, x.second);
    x.first /= temp;
    x.second /= temp;
}

pair<int, int> add(pair<int, int> x, pair<int, int> y) {
    auto p = make_pair(x.first*y.second + y.first*x.second, x.second*y.second);
    reduce(p);
    return p;
}

pair<int, int> subtract(pair<int, int> x, pair<int, int> y) {
    auto p = make_pair(x.first*y.second - y.first*x.second, x.second*y.second);
    reduce(p);
    return p;
}

pair<int, int> mult(pair<int, int> x, pair<int, int> y) {
    auto p = make_pair(x.first*y.first, x.second*y.second);
    reduce(p);
    return p;
}

pair<int, int> divide(pair<int, int> x, pair<int, int> y) {
    auto p = make_pair(x.first*y.second, x.second*y.first);
    reduce(p);
    return p;
}

void reduce(vector<vector<pair<int, int> > > &matrix) {
    int n = matrix.size(), m = matrix[0].size();
    for(int row = 0; row < n; ++row) {
        if(matrix[row][row].first == 0) {
            for(int i = row+1; i < n; ++i) {
                //find first non-zero element in submatrix
                if(matrix[i][row].first != 0) {
                    for(int j = row; j < matrix[i].size(); ++j) {
                        matrix[row][j] = add(matrix[row][j], matrix[i][j]);
                    }
                    break;
                }
            }
        }
        auto inverse = make_pair(matrix[row][row].second, matrix[row][row].first);
        for(int j = row; j < m; ++j) {
            matrix[row][j] = mult(matrix[row][j], inverse);
        }
        for(int i = 0; i < n; ++i) {
            if(i != row) {
                auto multiple = matrix[i][row];
                for(int j = row; j < matrix[i].size(); ++j) {
                    matrix[i][j] = subtract(matrix[i][j], mult(matrix[row][j], multiple));
                }
            }
        }
    }
}
void print(vector<vector<pair<int, int> > > &matrix) {
    for(auto &row : matrix) {
        for(auto &elem : row) {
            cout << elem.first << '/' << elem.second << ' ';
        }
        cout << '\n';
    }
}

int main() {
    //usage:
    vector<vector<pair<int, int> > > matrix;
    matrix = {{{1,1},{2,1},{3,1},{4,1}},{{2,1},{15,1},{4,1},{1,1}},{{0,1},{-3,1},{2,1},{1,1}}};
    //input matrix here
    cout << "before Row-reducing:\n";
    print(matrix);
    reduce(matrix);
    cout << "after Row-reducing:\n";
    print(matrix);
    return 0;
}
