// https://github.com/Ajayreddy17/Competitive_programming/blob/main/Combinatorial/combinatorics.cpp
// Coded by Aeren (https://codeforces.com/profile/Snow-Flower)
template<class T>
struct combinatorics{
    // O(n)
    static vector<T> precalc_fact(int n){
        vector<T> f(n + 1, 1);
        for(auto i = 1; i <= n; ++ i) f[i] = f[i - 1] * i;
        return f;
    }
    // O(n * m)
    static vector<vector<T>> precalc_C(int n, int m){
        vector<vector<T>> c(n + 1, vector<T>(m + 1));
        for(auto i = 0; i <= n; ++ i) for(auto j = 0; j <= min(i, m); ++ j) c[i][j] = i && j ? c[i - 1][j - 1] + c[i - 1][j] : T(1);
        return c;
    }
    int SZ = 0;
    vector<T> inv, fact, invfact;
    combinatorics(){ }
    // O(SZ)
    combinatorics(int SZ): SZ(SZ), inv(SZ + 1, 1), fact(SZ + 1, 1), invfact(SZ + 1, 1){
        for(auto i = 1; i <= SZ; ++ i) fact[i] = fact[i - 1] * i;
        invfact[SZ] = 1 / fact[SZ];
        for(auto i = SZ - 1; i >= 0; -- i){
            invfact[i] = invfact[i + 1] * (i + 1);
            inv[i + 1] = invfact[i + 1] * fact[i];
        }
    }
    // O(1)
    T C(int n, int k) const{
        return n < 0 ? C(-n + k - 1, k) * (k & 1 ? -1 : 1) : n < k || k < 0 ? T() : fact[n] * invfact[k] * invfact[n - k];
    }
    // O(1)
    T P(int n, int k) const{
        return n < k ? T() : fact[n] * invfact[n - k];
    }
    // O(1)
    T H(int n, int k) const{
        return C(n + k - 1, k);
    }
    // O(min(k, n - k))
    T naive_C(long long n, long long k) const{
        if(n < k) return 0;
        T res = 1;
        k = min(k, n - k);
        for(auto i = n; i > n - k; -- i) res *= i;
        return res * invfact[k];
    }
    // O(k)
    T naive_P(long long n, int k) const{
        if(n < k) return 0;
        T res = 1;
        for(auto i = n; i > n - k; -- i) res *= i;
        return res;
    }
    // O(k)
    T naive_H(long long n, int k) const{
        return naive_C(n + k - 1, k);
    }
    // O(1)
    bool parity_C(long long n, long long k) const{
        return n < k ? false : (n & k) == k;
    }
    // Number of ways to place n '('s and k ')'s starting with m copies of '(' such that in each prefix, number of '(' is equal or greater than ')'
    // Catalan(n, n, 0): n-th catalan number
    // O(1)
    T Catalan(int n, int k, int m = 0) const{
        assert(0 <= min({n, k, m}));
        return k <= m ? C(n + k, n) : k <= n + m ? C(n + k, n) - C(n + k, k - m - 1) : T();
    }
};
