// coded by Ajayreddy(https://codeforces.com/profile/ajayreddy12123)
template <class T>
struct cumulativesum{
    int n;
    vector<T> data;
    // O(n)
    cumulativesum(int n): n(n), data(n + 1, T(0)){}
    // O(n)
    cumulativesum(const vector<T> &v): n((int) v.size()), data(n + 1, T(0)) {
        for (int i = 0; i < n; i ++) data[i + 1] = data[i] + v[i];
    }
    // O(1)
    T query(int l, int r){
        assert(0 <= l and l <= r and r <= n);
        return data[r] - data[l];
    }
    // TODO: max_pred
};
