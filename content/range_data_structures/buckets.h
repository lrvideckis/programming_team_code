#pragma once

//this code isn't the best. It's meant as a rough start for sqrt-decomposition, and to be (heavily) modified
//doesn't handle overflow

//status: tested on random inputs, also used in various problems
struct buckets {
	const int BUCKET_SIZE = 50;//TODO: change - small value for testing

	struct bucket {
		int sumLazy = 0;
		int sumBucket = 0;
		int l, r;//inclusive range of bucket
		int len() const {
			return r - l + 1;
		}
	};

	vector<int> values;
	vector<bucket> _buckets;

	buckets(const vector<int>& initial) : values(initial) {
		int numBuckets = ((int)values.size() + BUCKET_SIZE - 1) / BUCKET_SIZE;
		_buckets.resize(numBuckets);
		for(int i = 0; i < numBuckets; i++) {
			_buckets[i].sumLazy = 0;
			_buckets[i].sumBucket = 0;
			_buckets[i].l = i * BUCKET_SIZE;
			_buckets[i].r = min((i + 1) * BUCKET_SIZE, (int)values.size()) - 1;
			for(int j = _buckets[i].l; j <= _buckets[i].r; j++)
				_buckets[i].sumBucket += values[j];
		}
	}

	void pushLazy(int bIdx) {
		bucket& b = _buckets[bIdx];
		if(!b.sumLazy) return;
		for(int i = b.l; i <= b.r; i++)
			values[i] += b.sumLazy;
		b.sumLazy = 0;
	}

	//update range [L,R]
	void update(int L, int R, int diff) {
		int startBucket = L / BUCKET_SIZE;
		int endBucket = R / BUCKET_SIZE;
		if(startBucket == endBucket) {//range contained in same bucket case
			for(int i = L; i <= R; i++) {
				values[i] += diff;
				_buckets[startBucket].sumBucket += diff;
			}
			return;
		}
		for(int bIdx : {
		            startBucket, endBucket
		        }) {//handle "endpoint" buckets
			bucket& b = _buckets[bIdx];
			for(int i = max(b.l, L); i <= min(b.r, R); i++) {
				values[i] += diff;
				b.sumBucket += diff;
			}
		}
		for(int i = startBucket + 1; i < endBucket; i++) { //handle all n/B buckets in middle
			bucket& b = _buckets[i];
			b.sumLazy += diff;
			b.sumBucket += b.len() * diff;
		}
	}

	//sum of range [L,R]
	int query(int L, int R) {
		int startBucket = L / BUCKET_SIZE;
		int endBucket = R / BUCKET_SIZE;
		if(startBucket == endBucket) {//range contained in same bucket case
			pushLazy(startBucket);
			int sum = 0;
			for(int i = L; i <= R; i++)
				sum += values[i];
			return sum;
		}
		int sum = 0;
		for(int bIdx : {
		            startBucket, endBucket
		        }) {//handle "endpoint" buckets
			bucket& b = _buckets[bIdx];
			pushLazy(bIdx);
			for(int i = max(b.l, L); i <= min(b.r, R); i++)
				sum += values[i];
		}
		for(int i = startBucket + 1; i < endBucket; i++) //handle all n/B buckets in middle
			sum += _buckets[i].sumBucket;
		return sum;
	}
};
