// https://github.com/Ajayreddy17/Competitive_programming/blob/main/Data_structures/Sparse_table/sparse_table.cpp
// Coded by Aeren (https://codeforces.com/profile/Snow-Flower)
template<class T, class F>
struct sparse_table{
    int n;
    vector<vector<T>> data;
    F TT;
    T T_id;
    sparse_table(){ }
    // O(n log n)
    sparse_table(const vector<T> &a, F TT, T T_id): n((int)a.size()), TT(TT), T_id(T_id), data({a}){
        for(auto p = 1, i = 1; p << 1 <= n; p <<= 1, ++ i){
            data.emplace_back(n - (p << 1) + 1);
            for(auto j = 0; j < (int)data[i].size(); ++ j) data[i][j] = TT(data[i - 1][j], data[i - 1][j + p]);
        }
    }
    // O(1)
    T query(int l, int r) const{
        assert(0 <= l && l <= r && r <= n);
        if(l == r) return T_id;
        int d = __lg(r - l);
        return TT(data[d][l], data[d][r - (1 << d)]);
    }
};
