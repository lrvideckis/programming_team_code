#pragma once
template <typename DS, typename... UPDATE_ARGS> struct update_priority_queue {

	DS ds;//any data structure with member functions `update` and `undo`

	using upd = pair<tuple<UPDATE_ARGS...>, map<int, int>::iterator>;
	vector<upd> upd_st;
	map<int/*priority*/, int/*index into update stack*/> mp;

	update_priority_queue(const DS& a_ds) : ds(a_ds) {}

	void pop_update() {//remove update with max priority
		assert(!upd_st.empty() && ssize(upd_st) == ssize(mp));
		vector<upd> extra;
		int idx = ssize(upd_st) - 1, lowest_pri = INT_MAX;
		for (auto it = mp.rbegin(); 2 * ssize(extra) < ssize(upd_st) - idx; it++) {
			int idx_sk = it->second;
			extra.push_back(upd_st[idx_sk]);
			idx = min(idx, idx_sk);
			lowest_pri = it->first;
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

	void push_update(UPDATE_ARGS... args, int priority) {
		ds.update(args...);
		auto [it, ins] = mp.emplace(priority, ssize(upd_st));
		assert(ins);//enforce distinct priorities
		upd_st.emplace_back(make_tuple(args...), it);
	}
};
