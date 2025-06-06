const int N = 2e5+5, LOG = 20;
vector<int> adj[N];
int up[N][LOG], depth[N];
 
void dfs(int u, int p = -1) {
    up[u][0] = p;
    for(int i=1; i<LOG; i++) {
        if(up[u][i-1] != -1) {
            up[u][i] = up[up[u][i-1]][i-1];
        }
        else up[u][i] = -1;
    }
 
    for(auto &v : adj[u]){
        if(v == p) continue;
        depth[v] = depth[u] + 1;
        dfs(v, u);
    }
}
 
int lift(int u, int k) {
    for(int mask=LOG-1; mask>=0; mask--) {
        if(k & (1 << mask)) {
            u = up[u][mask];
            if(u == -1) return -1;
        }
    }
    return u;
}
 
int lca(int u, int v) {
    if(depth[u] < depth[v]) swap(u, v);
    u = lift(u, depth[u]-depth[v]);
    if(u == v) return u + 1;
 
    for(int mask=LOG-1; mask>=0; mask--) {
        if(up[u][mask] != -1 && up[u][mask] != up[v][mask]) {
            u = up[u][mask];
            v = up[v][mask];
            if(u == -1) return 1;
        }
    }
    return up[u][0] + 1;
}