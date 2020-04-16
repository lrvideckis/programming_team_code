string s;
//z[i] is the length of the longest substring
//starting from s[i] which is also a prefix of s
int z[100010];//change size here
void zAlg() {
	int n = s.size();
	int L = 0, R = 0;
	for (int i = 1; i < n; i++) {
		if (i > R) {
			L = R = i;
			while (R < n && s[R-L] == s[R]) R++;
			z[i] = R-L; R--;
		} else {
			int k = i-L;
			if (z[k] < R-i+1) z[i] = z[k];
			else {
				L = i;
				while (R < n && s[R-L] == s[R]) R++;
				z[i] = R-L; R--;
			}
		}
	}
}
