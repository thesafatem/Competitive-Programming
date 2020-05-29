#include <iostream>
#include <vector>
#include <algorithm>
#define mp make_pair
using namespace std;

// ---------------------------------------------- BUILDING PART ---------------------------------------------- //

const int INF = 1e9 + 9;
const int MAXN = 5e5 + 5;
int fl[MAXN];

void count_sort(vector<int> &p, vector<int> &c) {			// sorting in linear time
	int n = int(p.size());
	vector<int> p_new(n), cnt(n), pos(n);					// complexity is O(n)
	for (int i = 0; i < n; i++) {							// because MAX_ELEMENT <= n
		cnt[c[i]]++;
	}
	for (int i = 1; i < n; i++) {
		pos[i] = pos[i - 1] + cnt[i - 1];
	}
	for (int i = 0; i < n; i++) {
		p_new[pos[c[p[i]]]] = p[i];
		pos[c[p[i]]]++;
	}
	p = p_new;
}

pair<vector<int>, vector<int> > sufmas(string s) {			// main function that builds
	int n = int(s.size());									// suffix array over given string s
	vector<pair<char, int> > a(n);	
	vector<int> p(n), c(n);									// works in O(nlogn)
															// because it has logn iterations
	for (int i = 0; i < n; i++) {							// in each iteration O(n) sorting is implemented
		a[i] = mp(s[i], i);
	}
	sort(a.begin(), a.end());

	for (int i = 0; i < n; i++) {
		p[i] = a[i].second;
	}
	c[p[0]] = 0;
	for (int i = 1; i < n; i++) {
		if (a[i].first == a[i - 1].first) {
			c[p[i]] = c[p[i - 1]];
		} else {
			c[p[i]] = c[p[i - 1]] + 1;
		}
	}

	int k = 0;
	while ((1 << k) < n) {
		for (int i = 0; i < n; i++) {
			p[i] = (p[i] - (1 << k) + n) % n;
		}
		count_sort(p, c);
		vector<int> c_new(n);
		c_new[p[0]] = 0;
		for (int i = 1; i < n; i++) {
			pair<int, int> prev, cur;
			prev = mp(c[p[i - 1]], c[(p[i - 1] + (1 << k)) % n]);
			cur = mp(c[p[i]], c[(p[i] + (1 << k)) % n]);
			if (prev == cur) {
				c_new[p[i]] = c_new[p[i - 1]];
			} else {
				c_new[p[i]] = c_new[p[i - 1]] + 1;
			}
		}
		c = c_new;
		k++;
	}

	return mp(p, c);
}

vector<int> build_lcp(string s, vector<int> &p, vector<int> &c) {		// builds lcp array that finds
	int n = int(s.size());												// length of two neighboring suffixes
	vector<int> lcp(n);													// in suffix array
	int k = 0;
	for (int i = 0; i < n - 1; i++) {									// complexity is O(|s|)
		int pi = c[i];
		int j = p[pi - 1];
		while (max(i + k, j + k) < n and s[i + k] == s[j + k]) {
			k++;
		}
		lcp[pi] = k;
		k = max(0, k - 1);
	}

	return lcp;
}

void precalc() {								// needs to precalculate logs
	fl[0] = 0;									// of all numbers in range [1, n]
	fl[1] = 0;									
	for (int i = 2; i < MAXN; i++) {			// complexity is O(n)				
		fl[i] = fl[i / 2] + 1;			
	}
}

vector<vector<int> > sparce_lcp(vector<int> &lcp) {		// builds sparce table on lcp
	precalc();											// needs to find lcp of two suffixes in O(1)
	int n = int(lcp.size());							
	vector<vector<int> > st(fl[n] + 1, vector<int>(n));
	for (int j = 0; j <= fl[n]; j++) {
		for (int i = 0; i < n; i++) {
			if (j == 0) {
				st[j][i] = lcp[i];
			} else {
				if (i + (1 << (j - 1)) < n) {
					st[j][i] = min(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
				} else {
					st[j][i] = INF;
					break;
				}
			}
		}
	}
	return st;
}

// ---------------------------------------------- APPLICATION PART ---------------------------------------------- //

string largest_common_substring(string s, string t) {	// finds the largest common substring of s and t
	int sz = int(s.size());								
	s = s + "@" + t + "$";								// works in O(|s + t|)
	int n = int(s.size());
	pair<vector<int>, vector<int> > pc = sufmas(s);
	vector<int> p = pc.first, c = pc.second;
	vector<int> lcp = build_lcp(s, p, c);
	int mx = 0;
	string ans = "";
	for (int i = 2; i < n; i++) {
		if ((p[i] < sz and p[i - 1] > sz) or (p[i] > sz and p[i - 1] < sz)) {
			if (lcp[i] > mx) {
				mx = lcp[i];
				ans = s.substr(min(p[i], p[i - 1]), mx);
			} else if (lcp[i] == mx) {
				ans = min(ans, s.substr(min(p[i], p[i - 1]), mx));
			}
		}
	}

	return ans;
}

long long different_substrings(string s) {				// finds the number if different substrings in s
	s = s + "$";										
	int n = int(s.size());								// complexity is O(|s|)
	pair<vector<int>, vector<int> > pc = sufmas(s);
	vector<int> p = pc.first, c = pc.second;
	vector<int> lcp = build_lcp(s, p, c);
	long long ans = 0;
	for (int i = 0; i < n; i++) {
		ans += (n - p[i] - 1 - lcp[i]);
	}

	return ans;
}

bool is_T_substring_of_S(string t, string s) {			// determines whether t is substring of s or not
	s = s + "$";										
	int n = s.size();									// single case complexity is O(|t|log|s|)
	pair<vector<int>, vector<int> > pc = sufmas(s);		
	vector<int> p = pc.first;							// if we have multiple queries on t
	int ts = t.size();									// we can once find suffix array
	int l = 0, r = n - 1;								// and then answer on each query in O(|t|log|s|)
	while (l <= r) {									// total complexity is O(q|t|log|s|)
		int mid = l + r >> 1;		
		string pat = s.substr(p[mid], ts);
		if (pat == t) {
			return true;
		} else if (pat < t) {
			l = mid + 1;
		} else {
			r = mid - 1;
		}
	}
	return false;
}

void substring_sorting(string s, vector<pair<int, int> > &subs) {					// subs contains pairs (l, r)
	s = s + "$";																	// in 0-indexing that are the
	int n = int(s.size());															// left and right ends of substring
	pair<vector<int>, vector<int> > pc = sufmas(s);
	vector<int> p = pc.first, c = pc.second;										// algorithm sorts these substrings
	vector<int> lcp = build_lcp(s, p, c);			 								// in lexicographical order
	vector<vector<int> > st = sparce_lcp(lcp);
	sort(subs.begin(), subs.end(), [&](pair<int, int> a, pair<int, int> b){			// main part of algorithm is
		if (a == b) return false;													// its comparator which works
		if (a.first == b.first) return a.second < b.second;							// in O(1) due to the sparce table
		int l = min(c[a.first], c[b.first]);										// over lcp array
		l++;
		int r = max(c[a.first], c[b.first]);
		int j = fl[r - l + 1];
		int mn = min(st[j][l], st[j][r - (1 << j) + 1]);
		if (a.second - a.first + 1 <= mn or b.second - b.first + 1 <= mn) {
			if (a.second - a.first == b.second - b.first) return a.first < b.first;
			else return a.second - a.first < b.second - b.first;
		} else {
			return s[a.first + mn] < s[b.first + mn];
		}
	});
}

// -------------------------------------------------------------------------------------------------------------- //

int main() {
	return 0;
}