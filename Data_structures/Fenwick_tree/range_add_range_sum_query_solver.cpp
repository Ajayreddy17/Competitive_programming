// https://github.com/Ajayreddy17/Competitive_programming/blob/main/Data_structures/Fenwick_tree/range_add_range_sum_query_solver.cpp
// Coded by Aeren (https://codeforces.com/profile/Snow-Flower)
template<class T>
struct range_add_range_sum_query_solver{
	int n;
	vector<T> data0, data1;
	range_add_range_sum_query_solver(){ }
	// O(n)
	range_add_range_sum_query_solver(int n): n(n), data0(n), data1(n){ }
	// O(n)
	range_add_range_sum_query_solver(int n, T init): range_add_range_sum_query_solver(vector<T>(n, init)){ }
	// O(n)
	range_add_range_sum_query_solver(const vector<T> &v): n((int)v.size()), data0(n), data1(v){
		for(auto i = 1; i <= n; ++ i) if(i + (i & -i) <= n) data1[i + (i & -i) - 1] += data1[i - 1];
	}
	void update(int ql, int qr, T x){
		assert(0 <= ql && ql <= qr && qr <= n);
		if(ql == qr) return;
		for(auto l = ql + 1; l <= n; l += l & -l) data0[l - 1] += x, data1[l - 1] -= ql * x;
		for(auto r = qr + 1; r <= n; r += r & -r) data0[r - 1] -= x, data1[r - 1] += qr * x;
	}
	T pref(int qr) const{
		assert(0 <= qr && qr <= n);
		T sum0 = {}, sum1 = {};
		for(auto r = qr; r > 0; r -= r & -r) sum0 += data0[r - 1], sum1 += data1[r - 1];
		return qr * sum0 + sum1;
	}
	T query(int l, int r) const{
		assert(0 <= l && l <= r && r <= n);
		return pref(r) - pref(l);
	}
	template<class output_stream>
	friend output_stream &operator<<(output_stream &out, const range_add_range_sum_query_solver<T> &solver){
		out << "[";
		for(auto i = 0; i < solver.n; ++ i){
			out << solver.query(i, i + 1);
			if(i != solver.n - 1) out << ", ";
		}
		return out << ']';
	}
};
