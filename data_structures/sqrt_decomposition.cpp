// SQRT Decomposition
struct Sqrt{
    int n, b;
    vector<long long> blocks, values;
    Sqrt(int _n) : n(_n), values(_n) {
        b = (int)sqrt(n) + 1;
        blocks = vector<long long>(b);
    }

    // Range update
    void update(int l, int r, int x) {
        int left = l / b;
        int right = r / b;
 
        if(left == right) {
            for(int i=l; i<=r; i++) {
                values[i] += x;
            }
        }
        else {
            for(int i=l; i<b*(left+1); i++) {
                values[i] += x;
            }
            for(int i=right*b; i<=r; i++) {
                values[i] += x;
            }
            for(int i=left+1; i<right; i++) {
                blocks[i] += x;
            }
        }
    }
    
    // Point query
    long long query(int k) {
        return blocks[k / b] + values[k];
    }
};