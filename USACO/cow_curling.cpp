#include <bits/stdc++.h>                        
#define pb push_back                            
#define mp make_pair                            
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)((x).size())
#define jonathan ios_base::sync_with_stdio(0)
#define livingston cin.tie(NULL); cout.tie(NULL)
using namespace std;                            
                                                
void yes() {cout << "Yes" << endl;}                                               
void no() {cout << "No" << endl;}                                                        
                                                
int dx[] = {1, 0, -1, 0, -1, -1, 1, 1};         
int dy[] = {0, 1, 0, -1, -1, 1, -1, 1}; 

const int INF = 1e9 + 9;
const long long LINF = 1e18 + 8;
const double EPS = 1e-9;
const long long MOD = 1e9 + 7; //998244353
const double PI = acos(-1);  

struct pt {
    long long x, y;

    pt() {}

    pt(long long _x, long long _y) {
        x = _x; y = _y;
    }
    
    pt operator+(const pt & p) const { return pt(x + p.x, y + p.y); }
    pt operator-(const pt & p) const { return pt(x - p.x, y - p.y); }
    long long cross(const pt & p) const { return x * p.y - y * p.x; }
    long long dot(const pt & p) const { return x * p.x + y * p.y; }
    long long cross(const pt & a, const pt & b) const { return (a - *this).cross(b - *this); }
    long long dot(const pt & a, const pt & b) const { return (a - *this).dot(b - *this); }
};

int orient(pt a, pt b, pt c) {
    long long d = (b.y - a.y) * (c.x - b.x) - (c.y - b.y) * (b.x - a.x);
    if (d == 0) return 0;
    else if (d < 0) return 1;
    else return 2;
}

long long dist2(pt a, pt b) {
    return ((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)); 
}

bool cmp(pt base, pt f, pt s) {
    int o = orient(base, f, s);
    if (o == 0) return dist2(base, f) < dist2(base, s);
    return o == 1;
}

vector<pt> convex_hull(vector<pt> &a) {
    int lowest = 0;
    for (int i = 0; i < sz(a); i++) {
        if (a[i].y < a[lowest].y or (a[i].y == a[lowest].y and a[i].x < a[lowest].x)) {
            lowest = i;
        }
    }
    swap(a[0], a[lowest]);
    pt base = a[0];
    sort(a.begin() + 1, a.end(), [&](pt f, pt s) {
        return cmp(base, f, s);
    });
    int k = 1;
    for (int i = 2; i < sz(a); i++) {
        while (k > 0 and orient(a[k - 1], a[k], a[i]) == 2) {
            k--;
        }
        swap(a[i], a[k + 1]);
        k++;
    }
    vector<pt> res;
    for (int i = 0; i <= k; i++) {
        res.pb(a[i]);
    }
    return res;
} 

bool inside_triangle(pt a, pt b, pt c, pt point) {
    if (orient(a, b, c) == 0 and orient(a, b, point) == 0) {
        return (fabs(sqrt(dist2(a, c)) - sqrt(dist2(a, point)) - sqrt(dist2(c, point))) < EPS);
    }
    long long s1 = abs(a.cross(b, c));
    long long s2 = abs(point.cross(a, b)) + abs(point.cross(b, c)) + abs(point.cross(c, a));
    return s1 == s2;
}

bool inside_polygon(vector<pt> &a, pt p) {
    int l = 2, r = sz(a) - 2;
    pt base = a[0];
    int ans = -1;
    while (l <= r) {
        int mid = l + r >> 1;
        if (orient(base, p, a[mid]) == 1) {
            r = mid - 1;
            ans = mid;
        } else {
            l = mid + 1;
        }
    }
    if (ans == -1) return inside_triangle(base, a[sz(a) - 2], a[sz(a) - 1], p);
    else return inside_triangle(base, a[ans - 1], a[ans], p);
}

void solve() {
    cout << orient(pt(1, 1), pt(10, 10), pt(3, 3)) << endl;
    int n; cin >> n;
    vector<pt> red(n), blue(n);
    for (int i = 0; i < n; i++) {
        cin >> red[i].x >> red[i].y;
    }
    for (int i = 0; i < n; i++) {
        cin >> blue[i].x >> blue[i].y;
    }
    vector<pt> red_hull = convex_hull(red);
    vector<pt> blue_hull = convex_hull(blue);
    int cnt_red = 0;
    int cnt_blue = 0;
    for (int i = 0; i < n; i++) {
        cnt_red += inside_polygon(red_hull, blue[i]);
        cnt_blue += inside_polygon(blue_hull, red[i]);
        
    }
    cout << cnt_red << " " << cnt_blue << endl;
}

int main() {
    freopen("curling.in", "r", stdin);
    freopen("curling.out", "w", stdout);
    jonathan; 
    livingston;
    solve();
    return 0;
}