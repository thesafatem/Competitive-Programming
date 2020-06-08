#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iomanip>
#define pb push_back
using namespace std;

struct pt {
	long long x, y;
};

int orientation(pt a, pt b, pt c) {
	long long d1 = (b.y - a.y) * (c.x - b.x);
	long long d2 = (c.y - b.y) * (b.x - a.x);
	if (d1 == d2) return 0;
	else if (d1 > d2) return 1;
	else return 2;
}

double dist(pt a, pt b) {
	return sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}

vector<pt> convex_hull(const vector<pt> &a) {
	int n = int(a.size());
	vector<int> used(n, false);
	vector<pt> res;
	int lowest = 0;
	for (int i = 0; i < n; i++) {
		if (a[i].x < a[lowest].x) {
			lowest = i;
		}
	}
	int last = lowest, cur;
	do {
		res.pb(a[last]);
		used[last] = true;
		cur = (last + 1) % n;
		for (int i = 0; i < n; i++) {
			if (i == last) continue;
			if (orientation(a[last], a[i], a[cur]) == 2) {
				cur = i;
			}
		}
		last = cur;
	} while (last != lowest);

	return res;
}

int main() {
	int n; cin >> n;
	vector<pt> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i].x >> a[i].y;
	}
	vector<pt> res = convex_hull(a);
	int sz = int(res.size());
	for (int i = 0; i < sz; i++) {
		cout << res[i].x << " " << res[i].y << endl;
	}
	return 0;
}