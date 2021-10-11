// Checks if two arrays are rotationally equvalent
// uses KMP with doubling trick
bool rot_eq(const vector<int> &a, const vector<int> &b) {
	if(a.size() != b.size()) return false;
	int n = a.size();
	vector<int> fail(n+1, 0);
	for(int i = 1, p = 0; i < n; i++) {
		while(p && a[i] != a[p]) p = fail[p];
		if(a[i] == a[p]) p++;
		fail[i + 1] = p;
	}
	for(int i = 0, p = 0; i < 2*n; i++) {
		int val = b[i%n];
		while(p && val != a[p]) p = fail[p];
		if(val == a[p]) p++;
		if(p == n) return true;
	}
	return false;
}
