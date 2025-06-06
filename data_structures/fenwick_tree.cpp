// Fenwick Tree 1-based indexing
struct FT{
    int n;
    vector<int> ft;
    FT(int _n) : n(_n), ft(_n+1) {}

    void add(int idx, int k) {
        for(; idx<=n; idx+=idx&-idx)
            ft[idx] += k;
    }
    int query(int idx) {
        int sum = 0;
        for(; idx>0; idx-=idx&-idx)
            sum += ft[idx];
        return sum;
    }
    int query(int l, int r) {
        return query(r) - query(l-1);
    }
};