//to avoid bits/stdc++.h include which slows down CI
//modifying this file will re-run all library checker tests
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <queue>
#include <cassert>
#include <string>
#include <array>
#include <numeric> //for iota
//for random numbers
#include <chrono>
#include <random>
#include <complex> //for kactl's FFT
#include <functional> //for lambdas
#include <climits> // for INT_MAX, INT_MIN
#include <optional>
using namespace std;

#define ssize(x) (int)(x).size()

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
