// Recursive segment tree
#define M ((l + r) >> 1)
// Point update, range query
struct ST{
    int n;
    vector<int> st;
    ST(int _n) : n(_n), st(4*_n) {}

    void build(int l, int r, int i) {
        if(l == r) {
            st[i] = values[l];
            return;
        }
        build(l, M, 2*i+1);
        build(M+1, r, 2*i+2);
        st[i] = st[2*i+1] + st[2*i+2];  // #!
    }
    void update(int l, int r, int idx, int x, int i) {
        if(l == r) {
            st[i] += x;
            return;
        }
        if(idx <= M) update(l, M, idx, x, 2*i+1);
        else update(M+1, r, idx, x, 2*i+2);
        st[i] = st[2*i+1] + st[2*i+2];
    }
    int query(int l, int r, int a, int b, int i) {
        if(a > r || b < l) return 0;
        if(a <= l && r <= b) return st[i];
        return query(l, M, a, b, 2*i+1) + query(M+1, r, a, b, 2*i+2);
    }
};  // l = 0, r = n-1, i = 0



// Range update, point query
// Use the same build function as above, but comment #!
void update(int l, int r, int a, int b, int x, int i) {
    if (a > r || b < l) return;
    if (a <= l && r <= b) {
        st[i] += x;
        return;
    }
    update(l, M, a, b, x, 2*i+1);
    update(M+1, r, a, b, x, 2*i+2);
}
int query(int l, int r, int idx, int i) {
    if(idx > r || idx < l) return 0;
    if(idx <= l && r <= idx) return st[i];
    return query(l, M, idx, 2*i+1) + query(M+1, r, idx, 2*i+2) + st[i];
}