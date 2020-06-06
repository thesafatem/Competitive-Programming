#include <iostream>
using namespace std;

void solve() {
	int n; cin >> n;
	int cnt = 0;
	int cube = 1;
	for (int i = 1; i <= n; i++) {
		cube *= 3;
	}
	for (int mask = 0; mask < (1 << n); mask++) {
		for (int submask = mask; ; submask = (submask - 1) & mask) {
			// operations with mask and submask
			cnt++;
			if (submask == 0) break;
		}
	}
	cout << cnt << " " << cube << endl;
}

int main() {
	solve();
}
