// Merge Sort Tree - A segment tree where each node stores a sorted vector
#define M ((l + r) >> 1)
struct ST{
    int n;
    vector<vector<int>> st;
    ST(int _n) : n(_n), st(4*_n) {}

    void build(int l, int r, int i, vector<int> &values) {
        if(l == r) {
            st[i].pb(values[l]);
            return;
        }
        build(l, M, 2*i+1, values);
        build(M+1, r, 2*i+2, values);
        st[i].resize(st[2*i+1].size() + st[2*i+2].size());
        merge(st[2*i+1].begin(), st[2*i+1].end(), st[2*i+2].begin(), st[2*i+2].end(), st[i].begin());
    }
    int query(int l, int r, int a, int b, int k, int i) {
        if(a > r || b < l) return 0;
        if(a <= l && r <= b) return st[i].end() - upper_bound(st[i].begin(), st[i].end(), k);
        return query(l, M, a, b, k, 2*i+1) + query(M+1, r, a, b, k, 2*i+2);
    }
};
