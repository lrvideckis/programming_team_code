//stolen from https://github.com/kth-competitive-programming/kactl/blob/main/stress-tests/utilities/genTree.h
vector<pair<int,int>> pruferCodeToTree(int n, const vector<int> &pruferCode) {
	// Stores number count of nodes in the prufer code
	unordered_map<int,int> nodeCount;

	// Set of integers absent in prufer code. They are the leaves
	set<int> leaves;

	int len = (int) pruferCode.size();
	int node = len + 2;

	// Count frequency of nodes
	for ( int i = 0; i < len; i++ ) {
		int t = pruferCode[i];
		nodeCount[t]++;
	}

	// Find the absent nodes
	for ( int i = 1; i <= node; i++ ) {
		if ( nodeCount.find ( i ) == nodeCount.end() ) leaves.insert ( i );
	}

	vector<pair<int,int>> edges;
	/*Connect Edges*/
	for ( int i = 0; i < len; i++ ){
		int a = pruferCode[i]; // First node

		//Find the smallest number which is not present in prufer code now
		int b = *leaves.begin(); // the leaf

		edges.push_back({a,b}); // Edge of the tree

		leaves.erase ( b ); // Remove from absent list
		nodeCount[a]--; // Remove from prufer code
		if ( nodeCount[a] == 0 ) leaves.insert ( a ); // If a becomes absent
	}

	// The final edge
	if(n > 1)
		edges.push_back({*leaves.begin(), *leaves.rbegin()});
	return edges;
}

vector<pair<int, int>> genRandomTreeViaPruferCode(int n) {
	vector<int> pruferCode;
	for (int i=0; i<n-2; i++) {
		pruferCode.push_back(getRand(1, n-1));
	}
	auto edges = pruferCodeToTree(n, pruferCode);
	for (auto &p: edges)
		p.first--, p.second--;
	return edges;
}

//if `heightLookUp` is close to n, it will generate trees with expected diameter length equal to O(log(n))
//if `heightLookUp` is small (like <10), this will generate long-stringy trees with long diameters
vector<pair<int,int>> genRandomTreeViaRandomParents(int n, int heightLookUp) {
	vector<int> perm(n);
	for(int i = 0; i < n; i++) perm[i] = i;
	for(int i = 0; i < n; i++) swap(perm[i], perm[getRand(i,n-1)]);//shuffle perm uniformly
	vector<pair<int,int>> edges;
	for(int i = 1; i < n; i++) {
		pair<int,int> edge = {i, getRand(max(0, i-heightLookUp), i-1)};
		edge.first = perm[edge.first];
		edge.second = perm[edge.second];
		edges.push_back(edge);
	}
	return edges;
}

vector<pair<int, int>> genRandomTree(int n) {
	int genType = getRand(1, 3);
	if(genType == 1) {
		return genRandomTreeViaPruferCode(n);
	}
	if(genType == 2) {
		return genRandomTreeViaRandomParents(n, getRand(1, n));
	}
	assert(genType == 3);
	return genRandomTreeViaRandomParents(n, getRand(1, 10));
}
