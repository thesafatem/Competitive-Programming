#include <bits/stdc++.h>                        
#define pb push_back                            
#define mp make_pair                            
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)((x).size())
#define jonathan ios_base::sync_with_stdio(0)
#define livingston cin.tie(NULL); cout.tie(NULL)
#define f first
#define s second
#define ull unsigned long long
#define endl '\n'
using namespace std;                            
                                                
void yes() {cout << "Yes" << endl;}                                               
void no() {cout << "No" << endl;}                                                        
                                                
int dx[] = {1, 0, -1, 0, -1, -1, 1, 1};         
int dy[] = {0, 1, 0, -1, -1, 1, -1, 1}; 

const int INF = 1e9 + 9;
const long long LINF = 1e18 + 8;
const double EPS = 1e-7;
const long long MOD = 1e9 + 7; //998244353
const double PI = acos(-1);  

vector<int> pf(string s) {
	int n = s.size();
	vector<int> pi(n);
	for (int i = 1; i < n; i++) {
		int j = pi[i - 1];
		while (j > 0 and s[j] != s[i]) {
			j = pi[j - 1];
		}
		if (s[i] == s[j]) j++;
		pi[i] = j;
	}
	return pi;
}

void solve() {
	string s; cin >> s;
	string t; cin >> t;
	int n = sz(s), m = sz(t);
	string st = t + '#' + s;
	vector<int> pi = pf(st);
	for (int i = m + 1; i < n + m + 1; i++) {
		if (pi[i] == m) {
			cout << i - 2 * m << " ";
		}
	}
	cout << endl;
}       


int main() {
    jonathan;
    livingston;
    bool test = false;
    int t = 1;
    if (test) cin >> t;
    for (int i = 0; i < t; i++) {
        solve();
    }
    return 0;
}