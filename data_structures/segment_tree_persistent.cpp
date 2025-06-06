#define M ((l + r) >> 1)
struct Node{
    int val;
    Node *left, *right;
    Node(int x) : val(x), left(NULL), right(NULL) {}        // Add value
    Node(Node *l, Node *r) : left(l), right(r), val(0) {    // Update values
        if(l) val += l->val;
        if(r) val += r->val;
    }
    Node(Node *root) : left(root->left), right(root->right), val(root->val) {}    // Make copy
};

Node *build(int l, int r) {
    if(l == r) return new Node(values[l]);
    return new Node(build(l, M), build(M+1, r));
}

Node *update(Node *node, int l, int r, int idx, int k) {
    if(l == r) return new Node(k);
    if(idx <= M) return new Node(update(node->left, l, M, idx, k), node->right);
    return new Node(node->left, update(node->right, M+1, r, idx, k));
}

int query(Node *node, int l, int r, int a, int b) {
    if(a > r || b < l) return 0;
    if(a <= l && r <= b) return node->val;
    return query(node->left, l, M, a, b) + query(node->right, M+1, r, a, b);
}
Node *roots[N];
// roots[copy++] = build(1, n);
// roots[copy++] = new Node(roots[idx]);   
// roots[copy] = update(roots[copy], 1, n, idx, x);
// query(roots[copy], 1, n, a, b)