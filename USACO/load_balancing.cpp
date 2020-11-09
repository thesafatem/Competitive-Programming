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

struct T {
    vector<int> t;

    T(int n) {
        t.resize(4 * n);
    }

    void pull(int v) {
        t[v] = t[2 * v] + t[2 * v + 1];
    }

    void update(int v, int tl, int tr, int id, int val) {
        if (tl > id or tr < id) return;
        else if (tl == tr and tl == id) {
            t[v] = val;
        } else {
            int mid = tl + tr >> 1;
            update(2 * v, tl, mid, id, val);
            update(2 * v + 1, mid + 1, tr, id, val);
            pull(v);
        }
    }

    int get(int v, int tl, int tr, int l, int r) {
        if (tl > r or tr < l or l > r) return 0;
        else if (tl >= l and tr <= r) return t[v];
        else {
            int mid = tl + tr >> 1;
            return get(2 * v, tl, mid, l, r) + get(2 * v + 1, mid + 1, tr, l, r);
        }
    }
};

void solve() {
    int n; cin >> n;
    int maxn = 1000002;
    vector<vector<int> > events(maxn + 10);
    vector<int> pos;
    T left = T(maxn);
    T right = T(maxn);
    vector<int> ys;
    for (int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        events[x].pb(y);
        int was = right.get(1, 1, maxn, y, y);
        right.update(1, 1, maxn, y, was + 1);
        pos.pb(x);
        ys.pb(y - 1);
        ys.pb(y + 1);
    }
    sort(all(pos));
    auto last = unique(all(pos));
    pos.erase(last, pos.end());
    sort(all(ys));
    last = unique(all(ys));
    ys.erase(last, ys.end());
    int ans = INF;
    for (int j = 0; j <= sz(pos); j++) {
        int l = 0, r = sz(ys) - 1;
        while (l <= r) {
            int mid = l + r >> 1;
            int y = ys[mid];
            int vverx = max(left.get(1, 1, maxn, 1, y), right.get(1, 1, maxn, 1, y));
            int vniz = max(left.get(1, 1, maxn, y + 1, maxn), right.get(1, 1, maxn, y + 1, maxn));
            ans = min(ans, max(vverx, vniz));
            if (vverx >= vniz) {
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        if (j == sz(pos)) break;
        int x = pos[j];
        for (int i = 0; i < sz(events[x]); i++) {
            int y = events[x][i];
            int was = left.get(1, 1, maxn, y, y);
            left.update(1, 1, maxn, y, was + 1);
            was = right.get(1, 1, maxn, y, y);
            right.update(1, 1, maxn, y, was - 1);
        }
    }   
    cout << ans << endl;
}       


int main() {
    freopen("balancing.in", "r", stdin);
    freopen("balancing.out", "w", stdout);
    bool test = false;
    int t = 1;
    if (test) cin >> t;
    for (int i = 0; i < t; i++) {
        solve();
    }
    return 0;
}