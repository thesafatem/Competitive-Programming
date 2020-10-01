#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Z-function stores the longest common prefix of the string and each of its suffixes

// ---------------------------------------------- BUILDING PART ---------------------------------------------- //

vector<int> Zfunc(string s) {									
	int n = int(s.size());
	vector<int> z(n, 0);									// Z[0] is said to be 0, but sometimes it can be |s|
	int l = 0, r = 0;										// [l, r] is the farthest coincidence with prefix
	for (int i = 1; i < n; i++) {
		if (i <= r) {										// if i is inside [l, r], we can surely say that
			z[i] = min(z[i - l], r - i + 1);				// z[i] is at least as big as minimum of length [i, r]
		}													// and already calculated Z at the image of ith position
 		while (z[i] + i <= n and s[z[i] + i] == s[z[i]]) {	
			z[i]++;											// naive increment of Z, while coincide
		}
		if (i + z[i] - 1 > r) {									// if we can move right bound farther
			l = i;											// we do it
			r = i + z[i] - 1;
		}
	}														// works in O(|s|), because naive part runs, if
															// right bound can be updated. but it can be updated 
	return z;												// only |s| times in total
}

vector<int> Z_from_P(vector<int> p) {
	int n = int(p.size());
	vector<int> z(n, 0);
	for (int i = 1; i < n; i++) {
		if (p[i] > 0) {
			z[i - p[i] + 1] = p[i]
		}
	}
	int i = 1;
	while (i < n) {
		int t = i;
		if (z[i] > 0) {
			for (int j = 1; j < z[i]; j++) {
				if (z[i + j] > z[j]) break;
				z[i + j] = min(z[j], z[i] - j);
				t = i + j;
			}
		}
		i = t + 1;
	}
	return z;
}

// ---------------------------------------------- APPLICATION PART ---------------------------------------------- //

string restore(vector<int> z) {
	int n = int(z.size());
	string s = "";
	int prefix = 0;
	int j = 0;
	char c = 'a';
	for (int i = 0; i < n; i++) {
		if (z[i] == 0 and prefix == 0) {
			s += c;
			if (c != 'z') c++;

		}
		if (z[i] > prefix) {
			j = 0;
			prefix = z[i];
		}
		if (prefix > 0) {
			s += s[j];
			j++;
			prefix--;
		}
	}
	vector<int> z_new = Zfunc(s);
	for (int i = 0; i < n; i++) {
		if (z[i] != z_new[i]) return "";
	}
	return s;
}

bool is_substring(string s, string t) {
	s = t + '$' + s;
	int sz = int(t.size());
	int n = int(s.size());
	vector<int> z = Zfunc(s);
	for (int i = sz + 1; i < n; i++) {
		if (z[i] == sz) {
			return true;
		}
	}
	return false;
}

string period(string s) {	
	vector<int> z = Zfunc(s);			
	int n = int(s.size());
	int r = n;							
	for (int i = 0; i < n; i++) {
		if (i + z[i] == n) {			
			r = i;
			break;
		}
	}

	return s.substr(0, r);
} 

bool is_cycle_shift(string s, string t) {
	s = t + '$' + s + s;
	int n = int(s.size());
	int sz = int(t.size());
	vector<int> z = Zfunc(s);
	for (int i = sz + 1; i < n; i++) {
		if (z[i] == sz) {
			return true;
		}
	}
	return false;
}

vector<int> number_of_prefix_occurences(string s) {
	int n = int(s.size());
	vector<int> z = Zfunc(s);
	vector<int> cnt(n + 1, 0);
	z[0] = n;
	for (int i = 0; i < n; i++) {
		cnt[z[i]]++;
	}
	for (int i = n - 1; i >= 1; i--) {
		cnt[i] += cnt[i + 1];
	}
	return cnt;
}

string longest_palindromic_prefix(string s) {
	string t = s;
	reverse(t.begin(), t.end());
	s = s + '$' + t;
	int n = int(s.size());
	vector<int> z = Zfunc(string s);
	int r = 1;
	for (int i = sz + 1; i < n; i++) {
		if (i + z[i] == n) {
			r = z[i];
			break;
		}
	}
	return s.substr(0, z[i]);
}

string shortest_superstring(string s, string t) {
	int n = int(s.size());
	int t = int(t.size());
	string a = s + '$' + t;
	string b = t + '$' + s;
	vector<int> za = Zfunc(a);
	vector<int> zb = Zfunc(b);
	string res = s + t;
	int len = n + m;
	for (int i = n + 1; i < n + m + 1; i++) {
		if (za[i] == n) {
			return t;
		} else if (i + za[i] == n + m + 1) {
			if (len > n + m - za[i]) {
				len = n + m - za[i];
				res = t + s.substr(za[i]);
				break;
			}
		}
	} 
	for (int i = m + 1; i < n + m + 1; i++) {
		if (zb[i] == m) {
			return s;
		} else if (i + zb[i] == n + m + 1) {
			if (len > n + m - zb[i]) {
				len = n + m - zb[i];
				res = s + t.substr(zb[i]);
				break;
			}
		}
	}
	return res;
}

int number_of_different_substrings(string s) {
	int n = int(s.size());
	string t = "";
	string res = 0;
	for (int i = n - 1; i >= 0; i--) {
		t = s[i] + t;
		vector<int> z = Zfunc(t);
		int mx = 0;
		for (int j = 0; i < n - i; j++) {
			mx = max(mx, z[j]);
		}
		res += n - i - mx;
	}

	return res;
}

// -------------------------------------------------------------------------------------------------------------- //

int main() {
	return 0;
}
