#include <bits/stdc++.h>
using namespace std;

long long disclog(long long a, long long b, long long m) {
	long long n = (long long)(sqrt(m)) + 1;
	long long an = 1;
	for (int i = 0; i < n; i++) {
		an = (an * a) % m;
	}
	map<long long, long long> vals;
	for (long long i = 1, cur = an; i <= n; i++) {
		if (!vals.count(cur)) {
			vals[cur] = i;
		}
		cur = (cur * an) % m;
	}
	for (long long i = 0, cur = b; i <= n; i++) {
		if (vals.count(cur)) {
			long long ans = vals[cur] * n - i;
			if (ans < m) return ans;
			cur = (cur * a) % m;
		}
	}
	return -1;
}

void solve() {
	// a^x = b (mod n)
	// x - ?
	long long a, b, m; cin >> a >> b >> m;
	cout << disclog(a, b, m) << endl;
}

int main() {
	solve();
	return 0;
}