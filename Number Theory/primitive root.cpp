#include <bits/stdc++.h>
#define pb push_back
using namespace std;

long long binpow(long long a, long long p, long long m) {
	if (p == 0) return 1;
	else if (p % 2 == 1) return a * binpow(a, p - 1, m) % m;
	else {
		long long res = binpow(a, p / 2, m);
		return res * res % m;
	}
}

long long primitive_root(long long m) {
	vector<long long> d;
	long long phi = m - 1, n = phi;
	for (long long i = 2; i * i <= n; i++) {
		if (n % i == 0) {
			d.pb(i);
			while (n % i == 0) {
				n /= i;
			}
		}
	}
	if (n > 1) {
		d.pb(n);
	}
	for (long long res = 2; res <= m; res++) {
		bool ok = true;
		for (int i = 0; i < int(d.size()); i++) {
			ok &= (binpow(res, phi / d[i], m) != 1);
		}
		if (ok) return res;
	}
	return -1;
}

void solve() {
	long long m; cin >> m;
	cout << primitive_root(m) << endl;
}

int main() {
	solve();
	return 0;
}