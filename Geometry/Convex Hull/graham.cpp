#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#define pb push_back
using namespace std;

const double eps = 1e-6;

struct pt {
	double x, y;
};

int orientation(pt a, pt b, pt c) {
	double d1 = (b.y - a.y) * (c.x - b.x);
	double d2 = (c.y - b.y) * (b.x - a.x);
	if (fabs(d1 - d2) < eps) return 0;
	else if (d1 - d2 < 0) return 1;
	else return 2;
}

double dist(pt a, pt b) {
	return sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}

bool cmp(pt base, pt f, pt s) {
	int o = orientation(base, f, s);
	if (o == 0) return dist(base, f) < dist(base, s);
	else return o == 1;
}

vector<pt> convex_hull(vector<pt> &a) {
	int n = int(a.size());
	int lowest = 0;
	for (int i = 0; i < n; i++) {
		if (a[i].y < a[lowest].y or (a[i].y == a[lowest].y and a[i].x < a[lowest].x)) {
			lowest = i;
		}
	}
	swap(a[0], a[lowest]);
	pt base = a[0];
	sort(a.begin() + 1, a.end(), [&](pt f, pt s) {
		return cmp(base, f, s);
	});
	int k = 1;
	for (int i = 2; i < n; i++) {
		while (k > 0 and orientation(a[k - 1], a[k], a[i]) == 2) {
			k--;
		}
		swap(a[i], a[k + 1]);
		k++;
	}	
	vector<pt> res;
	for (int i = 0; i <= k; i++) {
		res.pb(a[i]);
	}
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
}