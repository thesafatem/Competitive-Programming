#include <bits/stdc++.h>                        
#define pb push_back                            
#define mp make_pair                            
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)((x).size())
#define jonathan ios_base::sync_with_stdio(0)
#define livingston cin.tie(NULL); cout.tie(NULL)
using namespace std;                            
                                                
void yes() {cout << "YES" << endl;}                                               
void no() {cout << "NO" << endl;}                                                        
                                                
int dx[] = {1, 0, -1, 0, -1, -1, 1, 1};         
int dy[] = {0, 1, 0, -1, -1, 1, -1, 1}; 

const int INF = 1e9 + 9;
const long long LINF = 1e18 + 8;
const double EPS = 1e-6;
const long long MOD = 1e9 + 7; // 998244353
const double PI = acos(-1); 

struct pt {
    long long x, y;

    pt() {}
    pt(long long _x, long long _y) {
        x = _x; 
        y = _y;
    }

    pt operator+(const pt &p) const {
        return pt(x + p.x, y - p.y);
    }

    pt operator-(const pt &p) const {
        return pt(x - p.x, y - p.y);
    }

    long long cross(const pt &a) const {
        return x * a.y - a.x * y;
    }

    long long cross(const pt &a, const pt &b) const {
        return (a - *this).cross(b - *this);
    }
};

long long dist2(pt a, pt b) { 
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

bool inside_polygon(pt me, vector<pt> &pts) {
    pt p1 = pts.back() - pts[0];
    pt p2 = pts[1] - pts[0];
    pt pq = me - pts[0];

    if (!(p1.cross(pq) <= 0 && p2.cross(pq) >= 0)) return false;

    int l = 0, r = sz(pts);
    while (r - l > 1) {
        int mid = (l + r) / 2;
        pt cur = pt(pts[mid].x - pts[0].x, pts[mid].y - pts[0].y);
        if (cur.cross(pq) < 0) {
            r = mid;
        } else {
            l = mid;
        }
    }

    if (l == sz(pts) - 1) {
        return dist2(pts[0], me) <= dist2(pts[0], pts[l]);
    } else {
        pt l1 = pts[l + 1] - pts[l];
        pt lq = me - pts[l];
        return l1.cross(lq) >= 0;
    }
}

void reorder(vector<pt> &pts) {
    int base = 0;
    for(int i = 1; i < sz(pts); i++){
        if (pts[i].x < pts[base].x or (pts[i].x == pts[base].x && pts[i].y > pts[i].y)){
            base = i;
        }
    }
    rotate(pts.begin(), pts.begin() + base, pts.end());
}

void solve() {
    int n; cin >> n;
    vector<pt> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].x >> a[i].y;
    }
    reorder(a);
    pt me;
    cin >> me.x >> me.y;
    inside_polygon(me, a) ? yes() : no();
}

int main() {
    jonathan; 
    livingston;
    solve();
    return 0;
}