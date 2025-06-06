const int b = sqrt(N);
struct Queries{
    int l, r, idx;
    bool operator<(const Queries &other) const {
        if(l/b != other.l/b) return l < other.l;
        return (l/b & 1 ? r < other.r : r > other.r);
    }
};

// add(int idx)
// remove(int idx)
// get_res(int idx) 

void solve(vector<Queries> &queries) {
    sort(queries.begin(), queries.end());
    int l = 0, r = -1;
    for(auto &q : queries) {
        while(l > q.l) add(--l);
        while(r < q.r) add(++r);
        while(l < q.l) remove(l++);
        while(r > q.r) remove(r--);
        get_res();
    }
}