#pragma once

// Returns the longest palindrome
string cntPals(string &s) {
	string T = "";
	for(int i = 0; i < (int)s.size(); ++i) {
		T += "#" + s.substr(i,1);
	}
	T += '#';
	vector<int> P(T.size(),0);
	int center = 0, boundary = 0, maxLen = 0, resCenter = 0, cnt = 0;
	for(int i = 1; i+1 < (int)T.size(); ++i) {
		int iMirror = 2 * center - i;
		P[i] = (boundary > i ? min(boundary - i, P[iMirror]) : 0);
		while(i-1-P[i] >= 0 && i+1+P[i] <= (int)T.size()-1 && T[i+1+P[i]] == T[i-1-P[i]])
			P[i]++;
		if(i + P[i] > boundary) {
			center = i;
			boundary = i+P[i];
		}
		if(P[i] > maxLen) {
			maxLen = P[i];
			resCenter = i;
		}
		cnt += (P[i]+1)/2;
	}
	return s.substr((resCenter - maxLen)/2, maxLen);
	//return cnt;//number of palindromes
}
