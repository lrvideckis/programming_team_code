struct partitionFunction {
	vector<ll> remember;
	//The number of ways you can add to a number
 int getPartitionsModM(int n, int m) {
		if(n < 0) return 0;
		if(n == 0) return 1;
		if(remember.size() <= n) remember.resize(n+1,-1);
		if(remember[n] != -1) return remember[n];
	 int sum = 0;
	 int val = 1;
		for(int i = 1; val <= n; i++) {
		 int multiply = 1;
			if(i % 2 == 0) multiply = -1;
			val = ((3*i*i) + i) / 2;
			sum += getPartitionsModM(n - val, m) * multiply % m;
			val = ((3*i*i) - i) / 2;
			sum += getPartitionsModM(n - val, m) * multiply % m;
			sum %= m;
			if(sum < 0) sum += m;
		}
		return remember[n] = sum % m;
	}
};
