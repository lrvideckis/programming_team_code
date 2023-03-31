template <typename DS, typename... UPDATE_ARGS> struct update_priority_queue {

	DS ds;//any data structure with member functions `update` and `undo`

	//TODO: maybe add a `using` statement here to shorten the type
	vector<pair<tuple<UPDATE_ARGS...>, std::map<int, int>::iterator>> upd_st;//TODO: test if deque is faster
	map<int/*priority*/, int/*index into update stack*/> mp;

	update_priority_queue(const DS& a_ds) : ds(a_ds) {}

	void pop_update() {//remove update with max priority
		assert(!upd_st.empty() && ssize(upd_st) == ssize(mp));
		vector<pair<tuple<UPDATE_ARGS...>, std::map<int, int>::iterator>> highest_prio_upds;//TODO rename; TODO: see if I can change to vector<int> - indeces into upd_st
		int k = 1;//number of pops which we'll do
		int lowest_pri = INT_MAX;
		for(auto it = mp.rbegin(); 2 * ssize(highest_prio_upds) < k; it++) {
			int idx_sk = it->second;
			highest_prio_upds.push_back(upd_st[idx_sk]);
			k = max(k, ssize(upd_st) - idx_sk);
			assert(it->first < lowest_pri);
			lowest_pri = it->first;
		}

		{
			auto it = remove_if(upd_st.end() - k, upd_st.end(), [&](const auto& upd) {return upd.second->first >= lowest_pri;});
			assert(distance(it, upd_st.end()) == ssize(highest_prio_upds));
			reverse_copy(highest_prio_upds.begin(), highest_prio_upds.end(), it);
		}

		//TODO: golf this - maybe change definition of k
		int start_idx = ssize(upd_st) - k;

		assert(next(upd_st.back().second) == mp.end());
		upd_st.pop_back();
		mp.erase(prev(mp.end()));

		for(int i = start_idx; i < ssize(upd_st); i++)
			upd_st[i].second->second = i;

		assert(ssize(upd_st) - start_idx == k-1);

		while(k--) ds.undo();
		for(int i = start_idx; i < ssize(upd_st); i++)
			apply(&DS::update, tuple_cat(make_tuple(&ds), upd_st[i].first));
	}

	//assumes distinct priorities
	void push_update(UPDATE_ARGS... args, int priority) {
		assert(mp.find(priority) == mp.end());//enforce distinct priorities
		ds.update(args...);
		auto it = mp.emplace(priority, ssize(upd_st)).first;
		upd_st.emplace_back(make_tuple(args...), it);
	}
};
