// Checks if two arrays are rotationally equvalent
bool rot_eq(const vector<int> &a, const vector<int> &b) {
	if(a.size() != b.size()) return false;
	vector<int> fail(a.size()+1, 0);
	vector<int> both(b);
	both.insert(both.end(), b.begin(), b.end());
	int p = 0;
	for(int i = 1; i < (int)a.size(); i++) {
		while(p && a[i] != a[p]) p = fail[p];
		if(a[i] == a[p]) p++;
		fail[i + 1] = p;
	}
	p = 0;
	for(int i : both) {
		while(p && i != a[p]) p = fail[p];
		if(i == a[p]) p++;
		if(p == (int)a.size()) return true;
	}
	return false;
}
