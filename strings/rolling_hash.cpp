#define rep(i,a,b) for(int i=a;i<b;i++)
using ll = long long;

const int base = 251, MOD = 1e9+7;
vector<int> rolling_hash(string text, string pattern) {
    int n = text.length(), m = pattern.length();
    vector<ll> hashes(n+1), p(n+1);

    p[0] = 1;
    rep(i,1,n+1) p[i] = p[i-1] * base % MOD;

    rep(i,1,n+1) hashes[i] = (hashes[i-1] + (text[i-1]-'a'+1) * p[i-1] % MOD) % MOD;

    ll patternHash = 0;
    rep(i,1,m+1) patternHash = (patternHash + (pattern[i-1]-'a'+1) * p[i-1] % MOD) % MOD;

    vector<int> ocu;
    rep(i,0,n-m+1) {
        ll curr = (hashes[i+m] - hashes[i] + MOD) % MOD;
        if(curr == patternHash * p[i] % MOD) ocu.push_back(i);
    }
    return ocu;
}

// 0. Define 2 prime numbers: base and mod
// 1. Precompute powers of base
// 2. Compute prefix hashes of text
// 3. Compute hash of pattern
// 4. Sliding window of pattern size over the text to find matches