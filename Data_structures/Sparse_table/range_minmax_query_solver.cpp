// https://github.com/Ajayreddy17/Competitive_programming/blob/main/Data_structures/Sparse_table/range_minmax_query_solver.cpp
// Coded by Aeren (https://codeforces.com/profile/Snow-Flower)
// Specialization of sparse_table
// Range min query by default. Set cmp = greater and numeric limits to min for max query
template<class T, class Compare = less<>>
struct range_minmax_query_solver{
    int n;
    vector<vector<T>> data;
    Compare cmp;
    T T_id;
    range_minmax_query_solver(){ }
    // O(n log n)
    range_minmax_query_solver(const vector<T> &a, Compare cmp = less<>(), T T_id = numeric_limits<T>::max()): n((int)a.size()), cmp(cmp), T_id(T_id), data({a}){ // O(n log n)
        for(auto p = 1, i = 1; p << 1 <= n; p <<= 1, ++ i){
            data.emplace_back(n - (p << 1) + 1);
            for(auto j = 0; j < (int)data[i].size(); ++ j) data[i][j] = cmp(data[i - 1][j], data[i - 1][j + p]) ? data[i - 1][j] : data[i - 1][j + p];
        }
    }
    // O(1)
    T query(int l, int r) const{
        assert(0 <= l && l <= r && r <= n);
        if(l == r) return T_id;
        int d = __lg(r - l);
        return cmp(data[d][l], data[d][r - (1 << d)]) ? data[d][l] : data[d][r - (1 << d)];
    }
};
