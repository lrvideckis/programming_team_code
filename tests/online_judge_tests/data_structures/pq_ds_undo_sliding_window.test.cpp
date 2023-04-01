#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_3_D"
//since _GLIBCXX_DEBUG causes std::map insert/erase operations to be O(n)
#undef _GLIBCXX_DEBUG
#include "../template.hpp"

#include "../../../library/data_structures/priority_queue_of_updates.hpp"

struct stack_with_get_max {
	stack<pair<int, int>> st;
	void update(int val) {
		st.emplace(val, st.empty() ? val : min(val, st.top()));
	}
	void undo() {
		st.pop();
	}
	int get_max() const {
		return st.top().second;
	}
}

int main() {
	cin.tie(0)->sync_with_stdio(0);

	int n, l;
	cin >> n >> l;

	vector<int> arr(n);
	for(int i = 0; i < n; i++) cin >> arr[i];

	pq_updates<stack_with_get_max, int> pq{stack_with_get_max()};

	int priority = (n-l)/2;

	for(int i = 0; i < l; i++)
		pq.push_update(arr[i], priority--);

	cout << pq.ds.get_max() << " ";

	for(int i = l; i < n; i++) {
		pq.push_update(arr[i], priority--);
		pq.pop_update();
		cout << pq.ds.get_max() << " ";
	}

	return 0;
}
