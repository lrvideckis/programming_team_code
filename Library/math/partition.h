#pragma once

//status: not tested

struct partitionFunction {
	vector<long long> remember;
	//The number of ways you can add to a number
	long long getPartitionsModM(int n, int m) {
		if (n < 0) return 0;
		if (n == 0) return 1;
		if ((int) remember.size() <= n) remember.resize(n + 1, -1);
		if (remember[n] != -1) return remember[n];
		long long sum = 0;
		long long val = 1;
		for (int i = 1; val <= n; i++) {
			long long multiply = 1;
			if (i % 2 == 0) multiply = -1;
			val = ((3LL * i * i) + i) / 2;
			sum += getPartitionsModM(n - val, m) * multiply % m;
			val = ((3LL * i * i) - i) / 2;
			sum += getPartitionsModM(n - val, m) * multiply % m;
			sum %= m;
			if (sum < 0) sum += m;
		}
		return remember[n] = sum % m;
	}
};
