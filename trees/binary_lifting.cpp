const int N = 2e5+5, LOG = 20;
vector<int> adj[N];
int up[N][20];
 
void dfs(int u, int p = -1) {
    up[u][0] = p;
    for(int i=1; i<LOG; i++) {
        if(up[u][i-1] != -1)
            up[u][i] = up[up[u][i-1]][i-1];
        else up[u][i] = -1;
    }
 
    for(auto &v : adj[u]) {
        if(v == p) continue;
        dfs(v, u);
    }
}

int lift(int u, int k) {
    for(int mask=0; mask<LOG; mask++) {
        if(k & (1 << mask)) {
            u = up[u][mask];
            if(u == -1) return -1;
        }
    }
    return u + 1;
}