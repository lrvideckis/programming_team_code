struct disjointSet {
	vector<int> parent;
	disjointSet(int n) {
		parent.resize(n,-1);
	}
	int find(int x) {return parent[x] < 0 ? x : parent[x] = find(parent[x]);}
	void merge(int x, int y) {
		if((x=find(x)) == (y=find(y))) return;
		if(parent[y] < parent[x]) swap(x,y);
		parent[x] += parent[y];
		parent[y] = x;
	}
};
