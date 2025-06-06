// Trie dictionary
const int SIGMA = 26;
struct Node{
    vector<Node*> ocu;
    bool flag;
    Node() : ocu(SIGMA), flag(false) {}
};

struct Trie{
    Node *root;
    Trie() : root(new Node()) {}
    void insert(string word) {
        Node *curr = root;
        for(auto &it : word) {
            if(!curr -> ocu[it - 'a'])
                curr -> ocu[it - 'a'] = new Node();
            
            curr = curr -> ocu[it - 'a'];
        }
        curr -> flag = true;
    }
    bool search(string word) {
        Node *curr = root;
        for(auto &it : word) {
            if(!curr -> ocu[it - 'a']) 
                return false;
            curr = curr -> ocu[it - 'a'];
        }
        return curr -> flag;
    }
};