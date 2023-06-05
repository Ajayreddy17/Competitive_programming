// Coded by Aeren (https://codeforces.com/profile/Snow-Flower)
template<class T>
struct fenwick_tree_2d_sum{
    int n, m;
    vector<vector<T>> data;
    // O(n * m)
    fenwick_tree_2d_sum(const vector<vector<T>> &a): n((int)a.size()), m((int)a[0].size()), data(a){
        for(auto i = 1; i <= n; ++ i) if(i + (i & -i) <= n) for(auto j = 1; j <= m; ++ j) data[i + (i & -i) - 1][j - 1] += data[i - 1][j - 1];
        for(auto i = 1; i <= n; ++ i) for(auto j = 1; j <= m; ++ j) if(j + (j & -j) <= m) data[i - 1][j + (j & -j) - 1] += data[i - 1][j - 1];
    }
    // O(n * m)
    fenwick_tree_2d_sum(int n, int m): n(n), m(m), data(n, vector<T>(m)){}
    // a[p][q] += x
    // O(log n * log m)
    void update(int p, int q, T x){
        assert(0 <= p && p < n && 0 <= q && q < m);
        ++ p, ++ q;
        for(auto i = p; i <= n; i += i & -i) for(auto j = q; j <= m; j += j & -j) data[i - 1][j - 1] += x;
    }
    // Returns the sum of a[i][j] on [0, xr) X [0, yr)
    // O(log n * log m)
    T pref(int xr, int yr){
        assert(0 <= xr && xr <= n && 0 <= yr && yr <= m);
        T res{};
        for(auto i = xr; i > 0; i -= i & -i) for(auto j = yr; j > 0; j -= j & -j) res += data[i - 1][j - 1];
        return res;
    }
    // Returns the sum of a[i][j] on [xl, xr) X [yl, yr)
    // O(log n * log m)
    T query(int xl, int xr, int yl, int yr){
        assert(xl <= xr && yl <= yr);
        return pref(xr, yr) - pref(xr, yl) - pref(xl, yr) + pref(xl, yl);
    }
    // O(log n * log m)
    T query(int x, int y){
        return pref(x + 1, y + 1) - pref(x + 1, y) - pref(x, y + 1) + pref(x, y);
    }
    template<class output_stream>
    friend output_stream &operator<<(output_stream &out, const fenwick_tree_2d_sum<T> &fw){
        for(auto i = 0; i < fw.n; ++ i){
            out << "\n[";
            for(auto j = 0; j < fw.m; ++ j){
                out << fw.query(i, j);
                if(j != fw.m - 1) out << ", ";
            }
            out << "]\n";
        }
        return out;
    }
};
