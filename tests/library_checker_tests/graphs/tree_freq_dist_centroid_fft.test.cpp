#define PROBLEM "https://judge.yosupo.jp/problem/frequency_table_of_tree_distance"
#include "../../template.h"

#include "../../../library/graphs/centroid.h"


//source https://github.com/kth-competitive-programming/kactl/blob/main/content/numerical/FastFourierTransform.h
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef complex<double> C;
typedef vector<double> vd;
void fft(vector<C>& a) {
	int n = sz(a), L = 31 - __builtin_clz(n);
	static vector<complex<long double>> R(2, 1);
	static vector<C> rt(2, 1);  // (^ 10% faster if double)
	for (static int k = 2; k < n; k *= 2) {
		R.resize(n);
		rt.resize(n);
		auto x = polar(1.0L, acos(-1.0L) / k);
		rep(i, k, 2 * k) rt[i] = R[i] = i & 1 ? R[i / 2] * x : R[i / 2];
	}
	vi rev(n);
	rep(i, 0, n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
	rep(i, 0, n) if (i < rev[i]) swap(a[i], a[rev[i]]);
	for (int k = 1; k < n; k *= 2)
		for (int i = 0; i < n; i += 2 * k) rep(j, 0, k) {
			auto x = (double*)&rt[j + k], y = (double*)&a[i + j + k];    /// exclude-line
			C z(x[0]*y[0] - x[1]*y[1], x[0]*y[1] + x[1]*y[0]);           /// exclude-line
			a[i + j + k] = a[i + j] - z;
			a[i + j] += z;
		}
}
vd conv(const vd& a, const vd& b) {
	if (a.empty() || b.empty()) return {};
	vd res(sz(a) + sz(b) - 1);
	int L = 32 - __builtin_clz(sz(res)), n = 1 << L;
	vector<C> in(n), out(n);
	copy(all(a), begin(in));
	rep(i, 0, sz(b)) in[i].imag(b[i]);
	fft(in);
	for (C& x : in) x *= x;
	rep(i, 0, n) out[i] = in[-i & (n - 1)] - conj(in[i]);
	fft(out);
	rep(i, 0, sz(res)) res[i] = imag(out[i]) / (4 * n);
	return res;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n;
	cin >> n;
	vector<vector<int>> adj(n);
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	vector<int> parent = get_centroid_tree(adj);
	vector<vector<int>> childs(n);
	int root;
	for (int i = 0; i < n; i++) {
		if (parent[i] == -1)
			root = i;
		else
			childs[parent[i]].push_back(i);
	}
	vector<int> depth(n, 0);
	vector<int> vis(n, false);
	vector<long long> res(n, 0);
	auto dfs = [&](auto&& dfs, int node) -> void {

		auto szDfs = [&](auto&& szDfs, int node, int par, int currDist, vector<int>& cntDist) -> void {
			if(cntDist.size() <= currDist) cntDist.resize(currDist+1, 0);
			cntDist[currDist]++;

			for (int child : adj[node]) {
				if (child == par || vis[child]) continue;
				szDfs(szDfs, child, node, currDist + 1, cntDist);
			}
		};

		vector<double> totalCnt(1, 1.0);
		vis[node] = true;
		for (int child : adj[node]) {
			if (!vis[child]) {
				vector<int> cntDist;
				szDfs(szDfs, child, node, 1, cntDist);
				vector<double> tmpCntDist(cntDist.size());
				for (int i = 0; i < (int)cntDist.size(); i++) tmpCntDist[i] = cntDist[i];
				vector<double> prod = conv(totalCnt, tmpCntDist);
				for (int i = 1; i < (int)prod.size(); i++) {
					res[i] += prod[i] + 0.5;//for rounding
				}
				while (totalCnt.size() < cntDist.size()) totalCnt.push_back(0);
				for (int i = 1; i < (int)cntDist.size(); i++) totalCnt[i] += cntDist[i];
			}
		}

		for (int child : childs[node]) {
			depth[child] = 1 + depth[node];
			assert(depth[child] < 30 && (1 << depth[child]) <= n);
			dfs(dfs, child);
		}
	};
	dfs(dfs, root);
	for (int i = 1; i < n; i++)
		cout << res[i] << " ";
	cout << endl;
	return 0;
}
