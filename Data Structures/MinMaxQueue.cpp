#include <bits/stdc++.h>
using namespace std;

struct Stek {
	bool is_max;
	stack<pair<int, int> > vals;

	Stek() {}

	Stek(bool _is_max) {
		is_max = _is_max;
	}

	int size() {
		return vals.size();
	}

	bool empty() {
		return vals.empty();
	}

	int top() {
		if (empty()) return is_max ? INT_MIN : INT_MAX;
		return vals.top().first;
	}

	int get() {
		if (empty()) return is_max ? INT_MIN : INT_MAX;
		return vals.top().second;
	}

	void push(int x) {
		if (is_max) {
			vals.push(make_pair(x, max(x, vals.empty() ? x : vals.top().second)));
		} else {
			vals.push(make_pair(x, min(x, vals.empty() ? x : vals.top().second)));
		}
	}

	void pop() {
		if (!empty()) {
			vals.pop();
		}
	}
};

struct Que {
	bool is_max;
	Stek left, right;

	Que() {}

	Que(bool _is_max) {
		is_max = _is_max;
		left = Stek(is_max);
		right = Stek(is_max);
	}

	int size() {
		return left.size() + right.size();
	}

	bool empty() {
		return left.empty() and right.empty();
	}

	void carry() {
		if (left.empty()) {
			while (!right.empty()) {
				left.push(right.top());
				right.pop();
			}
		}
	}

	int front() {
		carry();
		return left.top();
	}

	int get() {
		carry();
		return is_max ? max(left.get(), right.get()) : min(left.get(), right.get());
	}

	void push(int x) {
		right.push(x);
	}

	void pop() {
		if (!empty()) {
			carry();
			left.pop();
		}
	}
};

int main() {
	int n; cin >> n;
	int k; cin >> k;
	vector<int> a(n);
	Que q = Que(true);

	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}

	for (int i = 0; i < k - 1; i++) {
		q.push(a[i]);
	}

	for (int i = k - 1; i < n; i++) {
		q.push(a[i]);
		cout << q.get() << " ";
		q.pop();
	}
	cout << endl;
}