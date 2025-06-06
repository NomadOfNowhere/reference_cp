struct Node{
    vector<Node*> ocu;
    Node() : ocu(2) {}
};

struct Trie {
    Node *root;
    Trie() : root(new Node()) { insert(0); }

    void insert(long long x) {
        Node *curr = root;
        for(int mask=63; mask>=0; mask--) {
            bool currBit = (x >> mask) & 1;
            if(!curr -> ocu[currBit]) 
                curr -> ocu[currBit] = new Node();
            curr = curr -> ocu[currBit];
        }
    }

    long long query(long long prefix) {
        Node *curr = root;
        long long res = 0;
        for(int mask=63; mask>=0; mask--) {
            bool currBit = (prefix >> mask) & 1;
            if(curr -> ocu[currBit ^ 1]) {
                res |= (1LL << mask);
                curr = curr -> ocu[currBit ^ 1];
            }
            else curr = curr -> ocu[currBit];
        }
        return res;
    }
};