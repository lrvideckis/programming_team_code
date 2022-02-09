#pragma once

//status: not tested, but used on various problems

const int K = 26;//character size

struct node {
	bool leaf = 0;
	int next[K], id, p = -1;
	char pch;
	node(int _p = -1, char ch = '#') : p(_p), pch(ch) {
		fill(next, next+K,-1);
	}
};

vector<node> t(1);//adj list

void add_string(const string& s, int id) {
	int c = 0;
	for(char ch : s) {
		int v = ch-'a';
		if(t[c].next[v] == -1) {
			t[c].next[v] = t.size();
			t.emplace_back(c,ch);
		}
		c = t[c].next[v];
	}
	t[c].leaf = 1;
	t[c].id = id;
}

void remove_string(const string& s) {
	int c = 0;
	for(char ch : s) {
		int v = ch-'a';
		if(t[c].next[v] == -1)
			return;
		c = t[c].next[v];
	}
	t[c].leaf = 0;
}

int find_string(const string& s) {
	int c = 0;
	for(char ch : s) {
		int v = ch-'a';
		if(t[c].next[v] == -1)
			return -1;
		c = t[c].next[v];
	}
	if(!t[c].leaf) return -1;
	return t[c].id;
}
