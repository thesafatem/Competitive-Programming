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
#define ll long long
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

struct query {
    int u, v, r, type;
    query() {}
    query(int _u, int _v, int _r, int _type) {
        u = _u; v = _v; r = _r; type = _type;
    }
};

vector<query> queries;

int p[100100];
int sz[100100];

void init(int n) {
    for (int i = 0; i <= n; i++) {
        p[i] = i;
        sz[i] = 1;
    }
}

int get(int v) {
    if (v == p[v]) return v;
    return p[v] = get(p[v]);
}

bool merge(int u, int v) {
    u = get(u);
    v = get(v);
    if (u == v) return false;
    if (sz[u] > sz[v]) swap(u, v);
    p[u] = v;
    sz[v] += sz[u];
    return true;
}

void solve() {
    int n, q; cin >> n >> q;
    for (int i = 0; i < n - 1; i++) {
        int u, v, r; cin >> u >> v >> r;
        queries.pb(query(u, v, r, 1));
    }

    for (int i = 0; i < q; i++) {
        int u, k; cin >> k >> u;
        queries.pb(query(u, u, k, 2 + i));
    }

    sort(all(queries), [&](query a, query b) {
        if (a.r == b.r) return a.type == 1;
        return a.r > b.r;
    });

    int ans[q];
    init(n);

    for (int i = 0; i < sz(queries); i++) {
        query ask = queries[i];
        if (ask.type == 1) {
            merge(ask.u, ask.v);
        } else {
            ans[ask.type - 2] = sz[get(ask.u)] - 1;
        }
    }

    for (int i = 0; i < q; i++) {
        cout << ans[i] << endl;
    }
}  

int main() {
    jonathan;
    livingston;
    freopen("mootube.in", "r", stdin);
    freopen("mootube.out", "w", stdout);
    bool test = 0;
    int t = 1;
    if (test) cin >> t;
    for (int i = 0; i < t; i++) {
        solve();
    }
    return 0;
}