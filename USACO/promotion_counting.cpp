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

int cost[100100];
vector<int> g[100100];
int a[100100];
int tin[100100], tout[100100], timer;

void dfs(int v, int p) {
    tin[v] = ++timer;
    a[tin[v]] = cost[v];
    for (int i = 0; i < sz(g[v]); i++) {
        int to = g[v][i];
        if (to == p) continue;
        dfs(to, v);
    }
    tout[v] = timer;
}

struct T {
    vector<vector<int> > t;

    T(int n) {
        t.resize(4 * n);
    }

    void pull(int v) {
        int l = 0, r = 0;
        while (l < sz(t[2 * v]) and r < sz(t[2 * v + 1])) {
            if (t[2 * v][l] < t[2 * v + 1][r]) {
                t[v].pb(t[2 * v][l++]);
            } else {
                t[v].pb(t[2 * v + 1][r++]);
            }
        }
        while (l < sz(t[2 * v])) {
            t[v].pb(t[2 * v][l++]);
        }
        while (r < sz(t[2 * v + 1])) {
            t[v].pb(t[2 * v + 1][r++]);
        }
    }

    void build(int v, int tl, int tr) {
        if (tl == tr) {
            t[v].pb(a[tl]);
        } else {
            int mid = tl + tr >> 1;
            build(2 * v, tl, mid);
            build(2 * v + 1, mid + 1, tr);
            pull(v);
        }
    }

    int find(int v, int x) {
        int l = 0, r = sz(t[v]) - 1;
        int ans = INF;
        while (l <= r) {
            int mid = l + r >> 1;
            if (t[v][mid] > x) {
                ans = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        return max(0, sz(t[v]) - ans);
    }

    int get(int v, int tl, int tr, int l, int r, int x) {
        if (l > r or tl > r or tr < l) return 0;
        if (tl >= l and tr <= r) {
            return find(v, x);
        } else {
            int mid = tl + tr >> 1;
            return get(2 * v, tl, mid, l, r, x) + get(2 * v + 1, mid + 1, tr, l, r, x);
        }
    }
};

void solve() {
    int n; cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> cost[i];
    }
    for (int i = 2; i <= n; i++) {
        int x; cin >> x;
        g[x].pb(i);
        g[i].pb(x);
    }
    dfs(1, 0);
    T t = T(n);
    t.build(1, 1, n);
    for (int i = 1; i <= n; i++) {
        cout << t.get(1, 1, n, tin[i], tout[i], cost[i]) << endl;
    }
}       


int main() {
    freopen("promote.in", "r", stdin);
    freopen("promote.out", "w", stdout);
    bool test = false;
    int t = 1;
    if (test) cin >> t;
    for (int i = 0; i < t; i++) {
        solve();
    }
    return 0;
}