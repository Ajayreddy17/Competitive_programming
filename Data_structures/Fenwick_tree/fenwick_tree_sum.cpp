// Coded by Aeren (https://codeforces.com/profile/Snow-Flower)
template<class T>
struct fenwick_tree_sum{
    int n;
    vector<T> data;
    fenwick_tree_sum(){ }
    // O(n)
    fenwick_tree_sum(int n): n(n), data(n){ }
    // O(n)
    fenwick_tree_sum(int n, T init): fenwick_tree_sum(vector<T>(n, init)){ }
    // O(n)
    fenwick_tree_sum(const vector<T> &v): n((int)v.size()), data(v){
        for(auto i = 1; i <= n; ++ i) if(i + (i & -i) <= n) data[i + (i & -i) - 1] += data[i - 1];
    }
    fenwick_tree_sum(const fenwick_tree_sum &otr): n(otr.n), data(otr.data){
    }
    // O(log n)
    void update(int p, T x){
        assert(0 <= p && p < n);
        for(++ p; p <= n; p += p & -p) data[p - 1] += x;
    }
    // O(log n)
    T pref(int r) const{
        assert(0 <= r && r <= n);
        T s{};
        for(; r > 0; r -= r & -r) s += data[r - 1];
        return s;
    }
    // O(log n)
    T query(int l, int r) const{
        assert(l <= r);
        return pref(r) - pref(l);
    }
    // O(log n)
    T query(int p) const{
        return pref(p + 1) - pref(p);
    }
    // pred(sum[0, r)) is T, T, ..., T, F, F, ..., F
    // Returns max r with T
    // O(log n)
    int max_pref(auto pred) const{
        assert(pred({}));
        int p = 0;
        T sum{};
        for(auto pw = 1 << __lg(n + 1); pw; pw >>= 1) if(p + pw <= n && pred(sum + data[p + pw - 1])){
                sum += data[p + pw - 1];
                p += pw;
            }
        return p;
    }
    template<class output_stream>
    friend output_stream &operator<<(output_stream &out, const fenwick_tree_sum<T> &fw){
        out << "[";
        for(auto i = 0; i < fw.n; ++ i){
            out << fw.query(i);
            if(i != fw.n - 1) out << ", ";
        }
        return out << ']';
    }
};
