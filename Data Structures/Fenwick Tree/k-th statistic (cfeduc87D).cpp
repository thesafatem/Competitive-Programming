#include <iostream>
#include <cmath>
#include <vector>
#define keep_calm_and_become_orange ios_base::sync_with_stdio(0)
#define utochka_po_imeni_jonathan_livingston cin.tie(0)
using namespace std;
 
struct fenwick {
	vector<int> f;
	int n;
 
	void init(int _n) {
		n = _n;
		f.resize(_n + 1, 0);
	}
 
	void update(int i, int val) {
		int j = i;
		while (j <= n) {
			f[j] += val;
			j = (j | (j + 1));
		}
	}
 
	int get(int i) {
		int res = 0;
		int j = i;
		while (j >= 1) {
			res += f[j];
			j = (j & (j + 1)) - 1;
		}
		return res;
	}
 
	void build(const vector<int> &a) {
		for (int i = 0; i < a.size(); i++) {
			update(a[i], 1);
		}
	} 
};
 
int main() {
	keep_calm_and_become_orange;
    utochka_po_imeni_jonathan_livingston;
	int n, q; cin >> n >> q;
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
 
	fenwick f;
	f.init(n);
	f.build(a);
 
	for (int it = 0; it < q; it++) {
		int k; cin >> k;
		if (k > 0) {
			f.update(k, 1);
		} else {
			k = abs(k);
			int l = 1, r = n;
			while (l < r) {
				int mid = (l + r - 1) / 2;
				if (f.get(mid) < k) {
					l = mid + 1;
				} else {
					r = mid;
				}
			}
			f.update(r, -1);
		}
	}
 
	for (int i = 1; i <= n; i++) {
		if (f.f[i] != 0) {
			cout << i << endl;
			return 0;
		}
	}
 
	cout << 0 << endl;
 
	return 0;
}