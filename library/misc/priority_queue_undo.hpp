template <typename DS, typename... UPDATE_ARGS> struct update_priority_queue {

	DS ds;//any data structure with member functions `update` and `undo`

	update_priority_queue(const DS& a_ds) : ds(a_ds) {}

	void pop_update() {//remove update with max priority
	}

	void push_update(UPDATE_ARGS... args, int priority) {
		ds.update(args...);
	}
};
