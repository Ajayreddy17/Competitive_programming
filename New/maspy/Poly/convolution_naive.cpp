template <class T>
vector<T> convolution_naive(const vector<T>& a, const vector<T>& b) {
    int n = int(a.size()), m = int(b.size());
    vector<T> ans(n + m - 1);
    if (n < m) {
        for(int j = 0; j < m; j++) for(int i = 0; i < n; i++) ans[i + j] += a[i] * b[j];
    } else {
        for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) ans[i + j] += a[i] * b[j];
    }
    return ans;
}
