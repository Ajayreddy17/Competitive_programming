// Coded by Aeren (https://codeforces.com/profile/Snow-Flower)
// Requires Graph
template<class T>
struct bfs_forest{
	int n;
	vector<T> dist;
	vector<int> pv;
	vector<int> pe;
	vector<int> order;
	vector<int> pos;
	vector<int> root;
	vector<int> depth;
	vector<int> was;
	T T_id;
	bfs_forest(int n, T T_id = 0): T_id(T_id){
		init(n);
	}
	void init(int n){
		this->n = n;
		pv.assign(n, -1);
		pe.assign(n, -1);
		order.clear();
		pos.assign(n, -1);
		root.assign(n, -1);
		depth.assign(n, -1);
		dist.assign(n, T_id);
		was.assign(n, -1);
		attempt = 0;
	}
	int attempt = 0;
	vector<int> q;
	// O(n + m)
	// Requires graph
	template<class Graph, class F = plus<>>
	void bfs(const Graph &g, const vector<int> &src, bool clear_order = true, F UT = plus<>()){
		assert(n == g.n);
		++ attempt;
		if(clear_order) order.clear();
		q = src;
		for(auto u: src){
			was[u] = attempt;
			depth[u] = 0;
			dist[u] = T_id;
			root[u] = u;
			pv[u] = -1;
			pe[u] = -1;
		}
		for(auto it = 0; it < (int)q.size(); ++ it){
			int u = q[it];
			pos[u] = (int)order.size();
			order.push_back(u);
			for(auto id: g.adj[u]){
				if(g.ignore && g.ignore(id)) continue;
				auto &e = g.edge[id];
				int v = u ^ e.from ^ e.to;
				if(was[v] == attempt) continue;
				was[v] = attempt;
				depth[v] = depth[u] + 1;
				dist[v] = UT(e.cost, dist[u]);
				pv[v] = u;
				pe[v] = id;
				root[v] = root[u];
				q.push_back(v);
			}
		}
		q.clear();
	}
	// O(n + m)
	template<class Graph, class F = plus<>>
	void bfs_all(const Graph &g, F UT = plus<>()){
		for(auto u = 0; u < n; ++ u) if(!~depth[u]) bfs<Graph, F>(g, {u}, false, UT);
	}
	// O(n + m)
	template<class F = plus<>>
	void bfs_implicitly(auto get_deg, auto get_adj, const vector<int> &src, bool clear_order = true, F UT = plus<>()){
		++ attempt;
		if(clear_order) order.clear();
		q = src;
		for(auto u: src){
			was[u] = attempt;
			depth[u] = 0;
			dist[u] = T_id;
			root[u] = u;
			pv[u] = -1;
			pe[u] = -1;
		}
		for(auto it = 0; it < (int)q.size(); ++ it){
			int u = q[it];
			pos[u] = (int)order.size();
			order.push_back(u);
			for(auto i = 0, deg = get_deg(u); i < deg; ++ i){
				auto [v, w] = get_adj(u, i);
				if(!~v || was[v] == attempt) continue;
				was[v] = attempt;
				depth[v] = depth[u] + 1;
				dist[v] = UT(w, dist[u]);
				pv[v] = u;
				pe[v] = i;
				root[v] = root[u];
				q.push_back(v);
			}
		}
		q.clear();
	}
	// O(n + m)
	template<class F = plus<>>
	void bfs_all_implicitly(auto get_deg, auto get_adj, F UT = plus<>()){
		for(auto u = 0; u < n; ++ u) if(!~depth[u]) bfs<F>(get_deg, get_adj, {u}, false, UT);
	}
};
