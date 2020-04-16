struct queueMax {
	stack<pair<ll, ll>> s1, s2;
	int size() {
		return s1.size() + s2.size();
	}
	bool isEmpty() {
		return (size() == 0);
	}
	void clear() {
		while(!s1.empty()) {
			s1.pop();
		}
		while(!s2.empty()) {
			s2.pop();
		}
	}
	ll getMax() {
		if(isEmpty()) {
			return -1e18;
		}
		if(!s1.empty() && !s2.empty()) {
			return max(s1.top().second, s2.top().second);
		}
		if(!s1.empty()) {
			return s1.top().second;
		}
		return s2.top().second;
	}
	void push(ll val) {
		if(s2.empty()) {
			s2.push({val, val});
		} else {
			s2.push({val, max(val, s2.top().second)});
		}
	}
	void pop() {
		if(s1.empty()) {
			while(!s2.empty()) {
				if(s1.empty()) {
					s1.push({s2.top().first, s2.top().first});
				} else {
					s1.push({s2.top().first, max(s2.top().first, s1.top().second)});
				}
				s2.pop();
			}
		}
		s1.pop();
	}
};
