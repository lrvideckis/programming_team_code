struct partitionFunction {
	vector<ll> remember;
	//The number of ways you can add to a number
	ll getPartitionsModM(ll n, ll m) {
		if(n < 0) return 0;
		if(n == 0) return 1;
		if(remember.size() <= n) remember.resize(n+1,-1);
		if(remember[n] != -1) return remember[n];
		ll sum = 0;
		ll val = 1;
		for(ll i = 1; val <= n; i++) {
			ll multiply = 1;
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
