/** @file */
#pragma once
/**
 * @see https://codeforces.com/blog/entry/111117
 * @code{.cpp}
 *     pq_updates<dsu_restorable, int, int> pq{dsu_restorable(n)};
 *     for (int i = 0; i < n; i++) pq.ds.add(i, initial_values[i]);
 *     pq.push_update(u, v, curr_pri);
 *     cout << pq.ds.sum(v) << '\n';
 * @endcode
 * @time n interweaved calls to pop_update, push_update take O(T(n)*nlogn)
 * where O(T(n)) = time complexity of DS::update and DS::undo
 */
template <typename DS, typename... ARGS> struct pq_updates {
	DS ds; /**< arbitrary data structure */
	using upd = pair<tuple<ARGS...>, map<int, int>::iterator>;
	vector<upd> upd_st; /**< stack of updates */
	map<int, int> mp; /**< priority -> index into update stack */
	/**
	 * @param a_ds any data structure with member functions `update` and `undo`
	 */
	pq_updates(const DS& a_ds) : ds(a_ds) {}
	/**
	 * Remove update with max priority
	 * @time O(log(n) + k*T(n)) where k = # of pops off the update stack
	 */
	void pop_update() {
		assert(!upd_st.empty());
		vector<upd> extra;
		int idx = ssize(upd_st) - 1, lowest_pri = INT_MAX;
		for (auto it = mp.rbegin(); 2 * ssize(extra) < ssize(upd_st) - idx; it++) {
			auto [pri, idx_sk] = *it;
			extra.push_back(upd_st[idx_sk]);
			idx = min(idx, idx_sk), lowest_pri = pri;
		}
		auto it = remove_if(upd_st.begin() + idx, upd_st.end(), [&](const auto & curr) {
			return curr.second->first >= lowest_pri;
		});
		reverse_copy(extra.begin(), extra.end(), it);
		for (int i = idx; i < ssize(upd_st); i++) ds.undo();
		upd_st.pop_back();
		mp.erase(prev(mp.end()));
		for (int i = idx; i < ssize(upd_st); i++) {
			apply(&DS::update, tuple_cat(make_tuple(&ds), upd_st[i].first));
			upd_st[i].second->second = i;
		}
	}
	/**
	 * @param args arguments to DS::update
	 * @param priority must be distinct, can be negative
	 * @time O(log(n) + T(n))
	 */
	void push_update(ARGS... args, int priority) {
		ds.update(args...);
		auto [it, ins] = mp.emplace(priority, ssize(upd_st));
		assert(ins);
		upd_st.emplace_back(make_tuple(args...), it);
	}
};
