#include <bits/stdc++.h>
using namespace std;

// TEMPLATEFINAL/DSU
struct DSU{
    int n;
    vector<int> parent, rank;
    DSU(int _n) : n(_n), parent(_n), rank(_n) {
        for(int i=0; i<n; i++) {
            make_set(i);
        }
    }
    int find_set(int v) {
        if (v == parent[v])
            return v;
        return parent[v] = find_set(parent[v]);
    }

    void make_set(int v) {
        parent[v] = v;
        rank[v] = 0;
    }

    void union_sets(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a != b) {
            if (rank[a] < rank[b])
                swap(a, b);
            parent[b] = a;
            if (rank[a] == rank[b])
                rank[a]++;
        }
    }

    int components() {
        int cnt = 0;
        for(int i=0; i<n; i++) {
            if(find_set(i) == i) {
                cnt++;
            }
        }
        return cnt;
    }
};



void solve() {
    int n, m1, m2, res, lenF, lenG;
    cin >> n >> m1 >> m2;
    DSU f(n), g(n);
    vector<pair<int, int>> adj1(m1);
    
    for(int i=0; i<m1; i++) {
        int u, v;
        cin >> u >> v;
        adj1[i] = {--u, --v};
    }

    for(int i=0; i<m2; i++) {
        int u, v;
        cin >> u >> v;
        g.union_sets(--u, --v);
    }

    res = 0;
    for(int i=0; i<m1; i++) {
        auto [u, v] = adj1[i];
        if(g.find_set(u) != g.find_set(v)) {
            res++;
        }
        else {
            f.union_sets(u, v);
        }
    }

    lenF = f.components(), lenG = g.components();
    res += lenF - lenG;
    
    cout << res << endl;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while(t--) {
        solve();
    }

    return 0;
}








/********* */


#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;

#define rep(i,a,b) for(int i=a;i<b;i++)
#define pb push_back
#define endl "\n"
#define all(x) x.begin(),x.end()
using ll = long long;

const int N = 2e5+5;
vector<pair<int, int>> adj[N];
bitset<N> heavy;
const int B = 2050;
vector<pair<int, int>> heavyVertices[N];
int values[N], deg[N];

// TEMPLATEFINAL/CUSTOMHASH
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
 
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
gp_hash_table<int, ll, custom_hash> colors[N];

void solve() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, q;
    cin >> n >> q;

    rep(i,0,n) cin >> values[i];

    rep(i,0,n-1) {
        int u, v, x;
        cin >> u >> v >> x;
        adj[--u].pb({--v, x});
        adj[v].pb({u, x});
    }

    ll res = 0;
    auto dfs = [&](auto self, int u, int p = -1) -> void {
        for(auto &[v, x] : adj[u]) {
            if(v == p) continue;
            if(values[u] != values[v]) res += 1ll * x;
            deg[u]++, deg[v]++;
            self(self, v, u);
        }
    };
    dfs(dfs, 0);

    rep(i,0,n) if(deg[i] >= B) heavy[i] = 1;

    rep(u,0,n) {
        if(heavy[u]) {
            for(auto &[v, x] : adj[u]) {
                colors[u][values[v]] += 1ll * x;
                if(heavy[v]) 
                    heavyVertices[u].pb({v, x});
                    heavyVertices[v].pb({u, x});
            }
        }
    }

    while(q--) {
        int u, c;
        cin >> u >> c;
        u--;

        if(heavy[u]) {
            res += 1ll * colors[u][values[u]];
            res -= 1ll * colors[u][c];
            for(auto &[v, x] : heavyVertices[u]) {
                colors[v][values[u]] -= 1ll * x;
                colors[v][c] += 1ll * x;
            }
            values[u] = c;
        }
        else {
            for(auto &[v, x] : adj[u]) {
                if(values[u] != values[v]) {
                    if(c == values[v]) res -= 1ll * x;
                }
                else {
                    if(c != values[v]) {
                        res += 1ll * x;
                    }
                }
                if(heavy[v]) {
                    colors[v][values[u]] -= 1ll * x;
                    colors[v][c] += 1ll * x;
                }
            }
            values[u] = c;
        }

        cout << res << endl;
    }

    rep(i,0,n) {
        adj[i].clear();
        heavyVertices[i].clear();
        colors[i].clear();
        deg[i] = 0;
        values[i] = 0;
    }
    heavy = 0;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while(t--) solve();
    return 0;
}




/********* */


#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=a;i<b;i++)
#define endl "\n"
#define pb push_back
#define all(x) x.begin(),x.end()
using ll = long long;

const int N = 1e5+5;
vector<pair<int, int>> adj[2*4*N];
ll dist[2*4*N];
int mp[N], vis[2*4*N];

void build(int l, int r, int i) {
    if (l == r) {
        mp[l] = i;
        adj[i].pb({i+4*N, 0});
        adj[i+4*N].pb({i, 0});
        return;
    }
    int m = (l+r)>>1;
    build(l, m, 2*i+1);
    build(m+1, r, 2*i+2);
    adj[i].pb({2*i+1, 0});
    adj[i].pb({2*i+2, 0});
    adj[2*i+1+4*N].pb({i+4*N, 0});
    adj[2*i+2+4*N].pb({i+4*N, 0});
}

void add(int l, int r, int u, int a, int b, int w, int op, int i) {
    if (a > r || b < l) return;
    if (a <= l && r <= b) {
        if(op == 2) adj[mp[u]].pb({i, w});
        else adj[i+4*N].pb({mp[u]+4*N, w});
        return;
    }
    int m = l+r>>1;
    add(l, m, u, a, b, w, op, 2*i+1);
    add(m+1, r, u, a, b, w, op, 2*i+2);
}

// TEMPLATEFINAL-DIJKSTRA
void dijkstra(int start, int n) {
    priority_queue<pair<ll, int>, vector<pair<ll,int>>, greater<pair<ll,int>>> pq;
    for(int i=0; i<2*4*N; i++) {
        dist[i] = 1e14;
    }

    dist[start] = 0;
    pq.push({0, start});

    while(!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if(vis[u]) continue;
        vis[u] = 1;

        for(auto &[v, w] : adj[u]) {
            if(dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);   
    int n, q, s;
    cin >> n >> q >> s;

    build(0, n-1, 0);

    auto dfs = [&](auto self, int u, int p = -1) -> void {
        cout << u << " - " << p << endl;
        vis[u] = 1;
        for(auto &[v, w] : adj[u]) {
            if(vis[v]) continue;
            self(self, v, u);
        }
    };
    // dfs(dfs, 0);

    while(q--) {
        int op, u, v, l, r, w;
        cin >> op;
        if(op == 1) {
            cin >> u >> v >> w;
            adj[mp[--u]].pb({mp[--v], w});
        }
        else {
            cin >> u >> l >> r >> w;
            add(0, n-1, --u, --l, --r, w, op, 0);
        }
    }
    dijkstra(mp[--s], n);
    rep(i,0,n) cout << (dist[mp[i]] != (ll)1e14 ? dist[mp[i]] : -1) << " ";
    cout << endl;

    return 0;
}





#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=a;i<b;i++)
#define endl "\n"
#define pb push_back
#define all(x) x.begin(),x.end()
using ll = long long;

// TEMPLATEFINAL/DIJKSTRA SEGMENT TREE
const int N = 1e5+5;
vector<pair<int, int>> adj[8*N];
ll dist[8*N];
int mp[2*N], n;

void build(int l, int r, int i) {
    if(l == r) {
        mp[l] = i;
        mp[n+l] = i+4*n;
        adj[i].pb({i+4*n, 0});
        adj[i+4*n].pb({i, 0});
        return;
    }
    int m = (l+r) >> 1;
    build(l, m, 2*i+1);
    build(m+1, r, 2*i+2);
    // cout << i << " " << 2*i+1 << " " << 2*i+2 << "    -    " << i+4*n << " " << 2*i+1+4*n << " " << 2*i+2+4*n << endl;
    adj[i].pb({2*i+1, 0});
    adj[i].pb({2*i+2, 0});
    adj[2*i+1+4*n].pb({i+4*n, 0});
    adj[2*i+2+4*n].pb({i+4*n, 0});
}

void dfs(int u, int p = -1) {
    cout << u << " " << p << endl;
    for(auto &[v, x] : adj[u]) {
        if(v == p) continue;
        dfs(v, u);
    }
}

void add(int l, int r, int u, int a, int b, int w, int op, int i) {
    if(a > r || b < l) return;
    if(a <= l && r <= b) {
        // cout << a << " " << b << " " << i << endl;
        // // cout << u << endl;
        if(op == 2) {
            adj[u].pb({i, w});
        }
        else {
            adj[i+4*n].pb({u+n, w});
        }
        return;
    }
    int m = (l + r) >> 1;
    add(l, m, u, a, b, w, op, 2*i+1);
    add(m+1, r, u, a, b, w, op, 2*i+2);
}

// TEMPLATEFINAL-DIJKSTRA
void dijkstra(int start, int n) {
    priority_queue<pair<ll, int>, vector<pair<ll,int>>, greater<pair<ll,int>>> pq;
    for(int i=0; i<n; i++) {
        dist[mp[i]] = 1e14;
    }

    dist[start] = 0;
    pq.push({0, start});

    while(!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if(d > dist[u]) continue;

        for(auto [v, w] : adj[u]) {
            if(dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
}


int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int q, s;
    cin >> n >> q >> s;

    build(0, n-1, 0);

    while(q--) {
        int op, u, v, l, r, w;
        cin >> op;
        // u, v, w
        if(op == 1) {
            cin >> u >> v >> w;
            adj[mp[--u]].pb({mp[--v], w});
        }
        // u, l, r, w
        else {
            cin >> u >> l >> r >> w;
            add(0, n-1, mp[--u], --l, --r, w, op, 0);
        }
    }
    dijkstra(mp[--s], n);
    rep(i,0,n) {
        cout << dist[mp[i]] << " "; cout << endl;
    }
    return 0;
}




/******* */


#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;

#define endl "\n"
// TEMPLATEFINAL/CUSTOMHASH
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
 
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
gp_hash_table<int, int,custom_hash> freq;
 
void solve() {
    int n, k, res = 0; cin >> n >> k;

    while(n--) {
        int x; cin >> x;
        if(freq[k-x] > 0) {
            res++;
            freq[k-x]--;
            freq[x]--;
        }
        freq[x]++;
    }
    cout << res << endl;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while(t--) {
        solve();
    }

    return 0;
}


/******** */


#include <bits/stdc++.h>
using namespace std;

// TEMPLATEFINAL/DSU
struct DSU{
    int n;
    vector<int> parent, rank;
    DSU(int _n) : n(_n), parent(_n), rank(_n) {
        for(int i=0; i<n; i++) {
            make_set(i);
        }
    }
    int find_set(int v) {
        if (v == parent[v])
            return v;
        return parent[v] = find_set(parent[v]);
    }

    void make_set(int v) {
        parent[v] = v;
        rank[v] = 0;
    }

    void union_sets(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a != b) {
            if (rank[a] < rank[b])
                swap(a, b);
            parent[b] = a;
            if (rank[a] == rank[b])
                rank[a]++;
        }
    }

    int components() {
        int cnt = 0;
        for(int i=0; i<n; i++) {
            if(find_set(i) == i) {
                cnt++;
            }
        }
        return cnt;
    }
};



void solve() {
    int n, m1, m2, res, lenF, lenG;
    cin >> n >> m1 >> m2;
    DSU f(n), g(n);
    vector<pair<int, int>> adj1(m1);
    
    for(int i=0; i<m1; i++) {
        int u, v;
        cin >> u >> v;
        adj1[i] = {--u, --v};
    }

    for(int i=0; i<m2; i++) {
        int u, v;
        cin >> u >> v;
        g.union_sets(--u, --v);
    }

    res = 0;
    for(int i=0; i<m1; i++) {
        auto [u, v] = adj1[i];
        if(g.find_set(u) != g.find_set(v)) {
            res++;
        }
        else {
            f.union_sets(u, v);
        }
    }

    lenF = f.components(), lenG = g.components();
    res += lenF - lenG;
    
    cout << res << endl;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while(t--) {
        solve();
    }

    return 0;
}



/******* */

// TEMPLATEFINAL-MOD INVERSE
// Calcula el extendido de euclides de forma recursiva
tuple<int, int, int> extendedGCD(int mod, int a) {
	if (a == 0) return {mod, 1, 0};
	auto[r, x, y] = extendedGCD(a, mod % a);
	return {r, y, x - mod / a * y};
}

// Calcula el inverso modular utilizando el extended GCD recursivo
int modInverse(int mod, int a) {
    auto[r, x, y] = extendedGCD(mod, a);
    if(r != 1) {
        return -1;
    }
    return ((y < 0) ? y+mod : y);
}




/*********** */


#include <bits/stdc++.h>
using namespace std;

#define endl "\n"
#define pb push_back
#define rep(i,a,b) for(int i=a;i<b;i++)
#define all(x) x.begin(), x.end()

// TEMPLATEFINAL/Convexhull
const double eps = 1e-9;
bool leq(double a, double b){return b-a >= -eps;}
bool le(double a, double b){return b-a > eps;}
bool eq(double a, double b){return fabs(a-b) <= eps;}

struct point{
    double x, y;
    int idx = -1;
    point(): x(0), y(0){}
    point(double x, double y): x(x), y(y){}
    point operator-(const point &p) const{return point(x - p.x, y - p.y);}
    point operator*(const int &k) const{return point(x * k, y * k);}
    bool operator<(const point &p) const{return le(x, p.x) || (eq(x, p.x)&& le(y, p.y));}
    bool operator==(const point &p) const{return eq(x, p.x) && eq(y, p.y);}
    double cross(const point &p) const{return x * p.y - y * p.x;}
};

istream &operator>>(istream &is, point &p){return is >> p.x >> p.y;}
ostream &operator<<(ostream &os, const point &p){return os << "(" << p.x << ", " << p.y << ")";}

vector<point> convexHull(vector<point> P) {
    sort(P.begin(), P.end());
    vector<point> L, U;
    for (int i = 0; i < P.size(); i++) {
        while (L.size() >= 2 && le((L[L.size() - 2] - P[i]).cross(L[L.size() - 1] - P[i]), 0)) {
            L.pop_back();
        }
        L.push_back(P[i]);
    }
    for (int i = P.size() - 1; i >= 0; i--) {
        while (U.size() >= 2 && le((U[U.size() - 2] - P[i]).cross(U[U.size() - 1] - P[i]), 0)) {
            U.pop_back();
        }
        U.push_back(P[i]);
    }
    L.pop_back();
    U.pop_back();
    L.insert(L.end(), U.begin(), U.end());
    return L;
}

bool pointInConvexHull(const vector<point> &poly, point p) {
    int n = poly.size();
    if(n < 3) return false;
    rep(i,0,n) {
        point a = poly[i], b = poly[(i+1) % n];
        double cp = (b - a).cross(p - a);
        if(!le(0, cp)) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n;
    double h;
    cin >> n >> h;

    vector<point> islands(n);
    vector<double> time(n), heights(n);
    rep(i,0,n) {
        cin >> islands[i] >> heights[i];
        islands[i].idx = i;
        time[i] = max(0.0, h - heights[i]);
    }

    double l = 0.0, r = *max_element(all(time));
    point c;
    cin >> c;
    auto valid = [&](double t) {
        vector<point> aux;
        rep(i,0,n) {
            if(t >= time[i]) aux.pb(islands[i]);
        }
        if(aux.size() < 3) return false;
        aux = convexHull(aux);
        return pointInConvexHull(aux, c);
    };

    if(!valid(r)) {
        cout << -1 << endl;
        return 0;
    }

    for(int it=0; it<100; it++) {
        double m = (l + r) / 2.0;
        if(valid(m)) {
            r = m;
        }
        else {
            l = m;
        }
    }
    cout << fixed << setprecision(12) << r << endl;

    return 0;
}