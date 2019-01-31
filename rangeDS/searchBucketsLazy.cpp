#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef long long ll;


// search_buckets provides two operations on an array:
// 1) do array[i] += x for i in range: [start, end)
// 2) count how many i in [start, end) satisfy array[i] < value
template<typename T>
struct search_buckets {
    // values are just the values in order. buckets are sorted in segments of BUCKET_SIZE (last segment may be smaller)
    int N, BUCKET_SIZE;
    vector<T> values, buckets, lazy;

    search_buckets(const vector<T> &initial = {}) {
        init(initial);
    }

    int get_bucket_end(int bucket_start) const {
        return min(bucket_start + BUCKET_SIZE, N);
    }

    void init(const vector<T> &initial) {
        values = buckets = initial;
        N = values.size();
        BUCKET_SIZE = 0.5*sqrt(N) + 1;
        lazy.resize((N+BUCKET_SIZE-1)/BUCKET_SIZE, 0);
        for (int start = 0; start < N; start += BUCKET_SIZE)
            sort(buckets.begin() + start, buckets.begin() + get_bucket_end(start));
    }

    int bucket_less_than(int bucket_start, T value) const {
        auto begin = buckets.begin() + bucket_start;
        auto end = buckets.begin() + get_bucket_end(bucket_start);
        return lower_bound(begin, end, (value-lazy[bucket_start/BUCKET_SIZE])) - begin;
    }

    int less_than(int start, int end, T value) const {
        if(start == end) return 0;
        int count = 0;
        int bucket_start = start - start % BUCKET_SIZE;
        int bucket_end = min(get_bucket_end(bucket_start), end);

        if (start - bucket_start < bucket_end - start) {
            while (start > bucket_start) {
                --start;
                count -= values[start] < (value-lazy[start/BUCKET_SIZE]);
            }
        } else {
            while (start < bucket_end) {
                count += values[start] < (value-lazy[start/BUCKET_SIZE]);
                ++start;
            }
        }

        if (start == end)
            return count;

        bucket_start = end - end % BUCKET_SIZE;
        bucket_end = get_bucket_end(bucket_start);

        if (end - bucket_start < bucket_end - end) {
            while (end > bucket_start) {
                --end;
                count += values[end] < (value-lazy[end/BUCKET_SIZE]);
            }
        } else {
            while (end < bucket_end) {
                count -= values[end] < (value-lazy[end/BUCKET_SIZE]);
                ++end;
            }
        }

        while (start < end && get_bucket_end(start) <= end) {
            count += bucket_less_than(start, value);
            start = get_bucket_end(start);
        }

        assert(start == end);
        return count;
    }
    
    void copy_and_sort(int bucket_start) {
        copy(values.begin()+bucket_start, values.begin()+get_bucket_end(bucket_start), buckets.begin()+bucket_start);
        sort(buckets.begin() + bucket_start, buckets.begin() + get_bucket_end(bucket_start));
    }
    
    void modify(int l, int r, T value) {
        if(l/BUCKET_SIZE == (r-1)/BUCKET_SIZE) {
            for(int i = l; i < r; ++i) {
                values[i] += value;
            }
            copy_and_sort(l/BUCKET_SIZE*BUCKET_SIZE);
            return;
        }
        const int start_bucket = (l+BUCKET_SIZE-1)/BUCKET_SIZE;
        const int end_bucket = (r-1)/BUCKET_SIZE;
        for(int i = l; i < start_bucket*BUCKET_SIZE; ++i) {
            values[i] += value;
        }
        copy_and_sort(l/BUCKET_SIZE*BUCKET_SIZE);
        for(int start = start_bucket; start < end_bucket; ++start) {
            lazy[start] += value;
        }
        for(int i = end_bucket*BUCKET_SIZE; i < r; ++i) {
            values[i] += value;
        }
        copy_and_sort((r-1)/BUCKET_SIZE*BUCKET_SIZE);
    }
};

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    const int n = 10000, maxn = 1000000;
    srand(time(NULL));
    vector<int> arr(n);
    for(int i = 0; i < n; ++i) {
        arr[i] = rand()%maxn;
    }
    search_buckets<int> sb(arr);
    for(int i = 0; i < n; ++i) {
        int type = rand()%2;
        int l = rand()%n;
        int r = rand()%n;
        if(l > r) swap(l,r);
        int value = rand()%maxn-maxn/2;
        if(type == 0) {//query
            int naive = 0;
            for(int j = l; j < r; ++j) {
                if(arr[j] < value) naive++;
            }
            //cout << naive << ' ' << sb.less_than(l,r,value) << '\n';
            if(naive != sb.less_than(l, r, value)) {
                cout << "incorrect\t" << naive << ' ' << sb.less_than(l,r,value) << '\n';
            }
            sb.less_than(l,r,value);
        } else {//update
            for(int j = l; j < r; ++j) {
                arr[j] += value;
            }
            sb.modify(l, r, value);
        }
    }
    return 0;
}


























