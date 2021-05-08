struct disjointSet {
	int numberOfSets;
	vector<int> parent;
	disjointSet(int n) : numberOfSets(n), parent(n,-1) {}
	int find(int x) {return parent[x] < 0 ? x : parent[x] = find(parent[x]);}
	int sizeOfSet(int x) {return -parent[find(x)];}
	bool merge(int x, int y) {
		if((x=find(x)) == (y=find(y))) return false;
		if(parent[y] < parent[x]) swap(x,y);
		parent[x] += parent[y];
		parent[y] = x;
		numberOfSets--;
		return true;
	}
};
