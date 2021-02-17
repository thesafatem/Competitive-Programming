#include <bits/stdc++.h>                        
#define pb push_back                            
#define mp make_pair                            
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)((x).size())
#define jonathan ios_base::sync_with_stdio(0)
#define livingston cin.tie(NULL); cout.tie(NULL)
#define fi first
#define se second
#define ull unsigned long long
#define ll long long
#define endl '\n'
using namespace std;                            
                                                
void yes() {cout << "Yes" << endl;}                                               
void no() {cout << "No" << endl;}                                                        
                                                
int dx[] = {1, 0, -1, 0, -1, -1, 1, 1};         
int dy[] = {0, 1, 0, -1, -1, 1, -1, 1}; 

const int INF = 1e9 + 9;
const long long LINF = 8e18 + 8;
const double EPS = 1e-7;
const long long MOD = 1e9 + 7; //998244353
const double PI = acos(-1); 

struct pt {
    int x, y;
    pt() {}
    pt (int _x, int _y) {
        x = _x; y = _y;
    }
};

void solve() {
    int n; cin >> n;
    vector<pt> a(n);
    int xmin = INF, ymin = INF, xmax = -INF, ymax = -INF;
    for (int i = 0; i < n; i++) {
        cin >> a[i].x >> a[i].y;
        xmin = min(xmin, a[i].x);
        xmax = max(xmax, a[i].x);
        ymin = min(ymin, a[i].y);
        ymax = max(ymax, a[i].y);
    }
    long long smax = 1ll * (xmax - xmin) * (ymax - ymin);
    sort(all(a), [&](pt p, pt q) {
        if (p.x == q.x) return p.y < q.y;
        return p.x < q.x;
    }); 
    xmin = INF; ymin = INF; xmax = -INF; ymax = -INF;
    long long smin = LINF;
    vector<pair<pt, pt> > suf(n);
    suf[n - 1] = mp(a[n - 1], a[n - 1]);
    for (int i = n - 2; i >= 0; i--) {
        suf[i].fi = pt(min(a[i].x, suf[i + 1].fi.x), min(a[i].y, suf[i + 1].fi.y));
        suf[i].se = pt(max(a[i].x, suf[i + 1].se.x), max(a[i].y, suf[i + 1].se.y));
    }
    for (int i = 0; i < n - 1; i++) {
        xmin = min(xmin, a[i].x);
        xmax = max(xmax, a[i].x);
        ymin = min(ymin, a[i].y);
        ymax = max(ymax, a[i].y);
        smin = min(smin, 1ll * (xmax - xmin) * (ymax - ymin) + 1ll * (suf[i + 1].se.x - suf[i + 1].fi.x) * (suf[i + 1].se.y - suf[i + 1].fi.y));
    }

    sort(all(a), [&](pt p, pt q) {
        if (p.y == q.y) return p.x < q.x;
        return p.y < q.y;
    });
    xmin = INF; ymin = INF; xmax = -INF; ymax = -INF;
    suf.clear();
    suf.resize(n);
    suf[n - 1] = mp(a[n - 1], a[n - 1]);
    for (int i = n - 2; i >= 0; i--) {
        suf[i].fi = pt(min(a[i].x, suf[i + 1].fi.x), min(a[i].y, suf[i + 1].fi.y));
        suf[i].se = pt(max(a[i].x, suf[i + 1].se.x), max(a[i].y, suf[i + 1].se.y));
    }
    for (int i = 0; i < n - 1; i++) {
        xmin = min(xmin, a[i].x);
        xmax = max(xmax, a[i].x);
        ymin = min(ymin, a[i].y);
        ymax = max(ymax, a[i].y);
        smin = min(smin, 1ll * (xmax - xmin) * (ymax - ymin) + 1ll * (suf[i + 1].se.x - suf[i + 1].fi.x) * (suf[i + 1].se.y - suf[i + 1].fi.y));
    }
    cout << smax - smin << endl;
}  

int main() {
    jonathan;
    livingston;
    freopen("split.in", "r", stdin);
    freopen("split.out", "w", stdout);
    bool test = 0;
    int t = 1;
    if (test) cin >> t;
    for (int i = 0; i < t; i++) {
        solve();
    }
    return 0;
}