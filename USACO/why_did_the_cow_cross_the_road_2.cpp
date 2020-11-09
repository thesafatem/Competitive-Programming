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

int a[100100], b[100100], pos[100100];

struct T {
    vector<int> t;

    T(int n) {
        t.resize(4 * n, 0);
    }

    void pull(int v) {
        t[v] = max(t[2 * v], t[2 * v + 1]);
    }

    void update(int v, int tl, int tr, int x, int val) {
        if (x > tr or x < tl) return;
        else if (tl == tr and tl == x) {
            t[v] = max(t[v], val);
        } else {
            int mid = tl + tr >> 1;
            update(2 * v, tl, mid, x, val);
            update(2 * v + 1, mid + 1, tr, x, val);
            pull(v);
        }
    }   

    int get(int v, int tl, int tr, int l, int r) {
        if (l > r) return 0;
        if (tl > r or tr < l) return -INF;
        else if (tl >= l and tr <= r) return t[v];
        else {
            int mid = tl + tr >> 1;
            return max(get(2 * v, tl, mid, l, r), get(2 * v + 1, mid + 1, tr, l, r));
        }
    }
};

void solve() {
    int n; cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pos[a[i]] = i;
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
    }

    T t = T(n);

    for (int i = 1; i <= n; i++) {
        vector<int> v;
        for (int j = max(1, b[i] - 4); j <= min(n, b[i] + 4); j++) {
            v.pb(pos[j]);
        }
        sort(all(v));
        reverse(all(v));
        for (int j = 0; j < sz(v); j++) {
            int id = v[j];
            int mx = t.get(1, 1, n, 1, id - 1);
            t.update(1, 1, n, id, mx + 1);
        }
    }
    int res = t.get(1, 1, n, 1, n);
    cout << res << endl;
}       


int main() {
    freopen("nocross.in", "r", stdin);
    freopen("nocross.out", "w", stdout);
    bool test = false;
    int t = 1;
    if (test) cin >> t;
    for (int i = 0; i < t; i++) {
        solve();
    }
    return 0;
}