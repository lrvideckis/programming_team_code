#pragma once
//stress tests: tests/stress_tests/range_data_structures/buckets.cpp
//this code isn't the best. It's meant as a rough start for sqrt-decomposition, and to be modified
//doesn't handle overflow
struct buckets {
	const int bucket_size = 50;//TODO: change - small value for testing
	struct node {
		int sum_lazy = 0;
		int sum_bucket = 0;
		int l, r;//inclusive range of bucket
		int len() const {
			return r - l + 1;
		}
	};
	vector<int> values;
	vector<node> bucket;
	buckets(const vector<int>& initial) : values(initial) {
		int numbucket = ((int)values.size() + bucket_size - 1) / bucket_size;
		bucket.resize(numbucket);
		for (int i = 0; i < numbucket; i++) {
			bucket[i].sum_lazy = 0;
			bucket[i].sum_bucket = 0;
			bucket[i].l = i * bucket_size;
			bucket[i].r = min((i + 1) * bucket_size, (int)values.size()) - 1;
			for (int j = bucket[i].l; j <= bucket[i].r; j++)
				bucket[i].sum_bucket += values[j];
		}
	}
	void push(int b_idx) {
		node& b = bucket[b_idx];
		if (!b.sum_lazy) return;
		for (int i = b.l; i <= b.r; i++)
			values[i] += b.sum_lazy;
		b.sum_lazy = 0;
	}
	//update range [l,r]
	void update(int l, int r, int diff) {
		int start_bucket = l / bucket_size;
		int end_bucket = r / bucket_size;
		if (start_bucket == end_bucket) { //range contained in same bucket case
			for (int i = l; i <= r; i++) {
				values[i] += diff;
				bucket[start_bucket].sum_bucket += diff;
			}
			return;
		}
		for (int b_idx : {
		            start_bucket, end_bucket
		        }) { //handle "endpoint" buckets
			node& b = bucket[b_idx];
			for (int i = max(b.l, l); i <= min(b.r, r); i++) {
				values[i] += diff;
				b.sum_bucket += diff;
			}
		}
		for (int i = start_bucket + 1; i < end_bucket; i++) { //handle all n/B buckets in middle
			node& b = bucket[i];
			b.sum_lazy += diff;
			b.sum_bucket += b.len() * diff;
		}
	}
	//sum of range [l,r]
	int query(int l, int r) {
		int start_bucket = l / bucket_size;
		int end_bucket = r / bucket_size;
		if (start_bucket == end_bucket) { //range contained in same bucket case
			push(start_bucket);
			int sum = 0;
			for (int i = l; i <= r; i++)
				sum += values[i];
			return sum;
		}
		int sum = 0;
		for (int b_idx : {
		            start_bucket, end_bucket
		        }) { //handle "endpoint" buckets
			node& b = bucket[b_idx];
			push(b_idx);
			for (int i = max(b.l, l); i <= min(b.r, r); i++)
				sum += values[i];
		}
		for (int i = start_bucket + 1; i < end_bucket; i++) //handle all n/B buckets in middle
			sum += bucket[i].sum_bucket;
		return sum;
	}
};
