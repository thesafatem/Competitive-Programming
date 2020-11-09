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

void update(int &cur_cow, int &cnt, int cow) {
    if (cnt == 0 or cur_cow == cow) {
        cur_cow = cow;
        cnt++;
    } else {
        cnt--;
    }
}

int calc(int cur_cow, int cnt, vector<int> cows) {
    sort(cows.begin() + 1, cows.end());
    while (cows.back() > 0) {
        for (int i = sz(cows) - 1; i > 0; i--) {
            update(cur_cow, cnt, i);
            cows[i]--;
            if (cows[i - 1] <= cows[i]) break;
        }
    }
    for (int i = 0; i < cows[0]; i++) {
        update(cur_cow, cnt, 0);
    }
    return cur_cow == 0 ? cnt : 0;
}

void solve() {
    int n, m; cin >> n >> m;
    vector<int> a(m);
    for (int i = 0; i < m; i++) {
        cin >> a[i];
    }
    int cur_cow = 0, cnt = 0;
    int res = calc(cur_cow, cnt, a);
    if (res <= 0) {
        cout << "NO" << endl;
        return;
    }
    cout << "YES" << endl;
    cout << res << endl;
    for (int i = 0; i < n; i++) {
        int p_cow = cur_cow;
        int p_cnt = cnt;
        for (int j = 0; j < m; j++) {
            if (a[j] == 0) continue;
            a[j]--;
            update(cur_cow, cnt, j);
            if (calc(cur_cow, cnt, a) == res) {
                cout << j + 1 << endl;
                break;
            } else {
                a[j]++;
                cur_cow = p_cow;
                cnt = p_cnt;
            }
        }
    }
}

int main() {
    freopen("gangs.in", "r", stdin);
    freopen("gangs.out", "w", stdout);
    jonathan; 
    livingston;
    solve();
    return 0;
}