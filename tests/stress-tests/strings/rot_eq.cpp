#include "../test_utilities/template.h"
#include "../test_utilities/generators/random.h"

#include "../../../Library/strings/rotationally_equivalent.h"

int main() {
	for(int tests = 200; tests--;) {
		int n = getRand(1, 5);//TODO

		auto gen = [&](vector<int>& arr, string& s) -> void {
			arr.resize(n);
			s = string(n,'a');
			assert((int)s.size() == n);
			for(int i = 0; i < n; i++) {
				arr[i] = getRand(0,3);
				s[i] = arr[i] + 'a';
			}
		};

		vector<int> arr1, arr2;
		string s1, s2;

		gen(arr1, s1);

		if(getRand(1, 3) == 1) {
			int rot = getRand(0, n-1);
			s2 = s1.substr(rot) + s1.substr(0,rot);
			arr2.resize(n);
			for(int i = 0; i < n; i++) {
				arr2[i] = s2[i] - 'a';
			}
		} else {
			gen(arr2, s2);
		}

		bool naiveRotEq = false;
		for(int i = 0; i < n; i++) {
			if(s1 == s2.substr(i) + s2.substr(0,i)) {
				naiveRotEq = true;
				break;
			}
		}

		assert(naiveRotEq == rot_eq<string>(s1, s2));
		assert(naiveRotEq == rot_eq<vector<int>>(arr1, arr2));
	}

	cout << "Tests passed!" << endl;
	return 0;
}
