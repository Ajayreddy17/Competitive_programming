// https://github.com/Ajayreddy17/Competitive_programming/blob/main/Graph_theory/Spanning_Forests/dfs_forest.cpp
// Coded by Aeren (https://codeforces.com/profile/Snow-Flower)
template<class T>
struct dfs_forest{
    int n;
    vector<T> dist;
    vector<int> pv;
    vector<int> pe;
    vector<int> order;
    vector<int> pos;
    vector<int> end;
    vector<int> size;
    vector<int> root;
    vector<int> depth;
    vector<int> min_depth;
    vector<int> min_depth_origin;
    vector<int> min_depth_spanning_edge;
    vector<int> was;
    T T_id;
    dfs_forest(int n, T T_id = 0): T_id(T_id){ init(n); }
    void init(int n){
        this->n = n;
        pv.assign(n, -1);
        pe.assign(n, -1);
        order.clear();
        pos.assign(n, -1);
        end.assign(n, -1);
        size.assign(n, 0);
        root.assign(n, -1);
        depth.assign(n, -1);
        min_depth.assign(n, -1);
        min_depth_origin.assign(n, -1);
        min_depth_spanning_edge.assign(n, -1);
        dist.assign(n, T_id);
        was.assign(n, -1);
        attempt = 0;
    }
    int attempt;
    // O(n + m)
    // Requires graph
    template<class Graph, class F = plus<>>
    void dfs(const Graph &g, int u, bool clear_order = true, F UT = plus<>()){
        assert(n == g.n);
        ++ attempt;
        depth[u] = 0;
        dist[u] = T_id;
        root[u] = u;
        pv[u] = pe[u] = -1;
        if(clear_order) order.clear();
        auto recurse = [&](auto self, int u)->void{
            was[u] = attempt;
            pos[u] = (int)order.size();
            order.push_back(u);
            size[u] = 1;
            min_depth[u] = depth[u];
            min_depth_origin[u] = u;
            min_depth_spanning_edge[u] = -1;
            for(auto id: g.adj[u]){
                if(id == pe[u] || g.ignore && g.ignore(id)) continue;
                auto &e = g.edge[id];
                int v = e.from ^ e.to ^ u;
                if(was[v] == attempt){
                    if(min_depth[u] > depth[v]){
                        min_depth[u] = depth[v];
                        min_depth_spanning_edge[u] = id;
                    }
                    continue;
                }
                depth[v] = depth[u] + 1;
                dist[v] = UT(e.cost, dist[u]);
                pv[v] = u;
                pe[v] = id;
                root[v] = root[u];
                self(self, v);
                size[u] += size[v];
                if(min_depth[u] > min_depth[v]){
                    min_depth[u] = min_depth[v];
                    min_depth_origin[u] = min_depth_origin[v];
                    min_depth_spanning_edge[u] = min_depth_spanning_edge[v];
                }
            }
            end[u] = (int)order.size();
        };
        recurse(recurse, u);
    }
    // O(n + m)
    template<class Graph, class F = plus<>>
    void dfs_all(const Graph &g, F UT = plus<>()){
        for(auto u = 0; u < n; ++ u) if(!~depth[u]) dfs<Graph, F>(g, u, false, UT);
    }
    // O(n + m)
    template<class F = plus<>>
    void dfs_implicitly(auto get_deg, auto get_adj, int u, bool clear_order = true, F UT = plus<>()){
        ++ attempt;
        depth[u] = 0;
        dist[u] = T_id;
        root[u] = u;
        pv[u] = pe[u] = -1;
        if(clear_order) order.clear();
        auto recurse = [&](auto self, int u)->void{
            was[u] = attempt;
            pos[u] = (int)order.size();
            order.push_back(u);
            size[u] = 1;
            min_depth[u] = depth[u];
            min_depth_origin[u] = u;
            min_depth_spanning_edge[u] = -1;
            for(auto i = 0, deg = get_deg(u); i < deg; ++ i){
                auto [v, w] = get_adj(u, i);
                if(!~v) continue;
                if(was[v] == attempt){
                    if(min_depth[u] > depth[v]){
                        min_depth[u] = depth[v];
                        min_depth_spanning_edge[u] = i;
                    }
                    continue;
                }
                depth[v] = depth[u] + 1;
                dist[v] = UT(w, dist[u]);
                pv[v] = u;
                pe[v] = i;
                root[v] = root[u];
                self(self, v);
                size[u] += size[v];
                if(min_depth[u] > min_depth[v]){
                    min_depth[u] = min_depth[v];
                    min_depth_origin[u] = min_depth_origin[v];
                    min_depth_spanning_edge[u] = min_depth_spanning_edge[v];
                }
            }
            end[u] = (int)order.size();
        };
        recurse(recurse, u);
    }
    // O(n + m)
    template<class F = plus<>>
    void dfs_all_implicitly(auto get_deg, auto get_adj, F UT = plus<>()){
        for(auto u = 0; u < n; ++ u) if(!~depth[u]) dfs<F>(get_deg, get_adj, u, false, UT);
    }
    bool ancestor_of(int u, int v) const{
        return pos[u] <= pos[v] && end[v] <= end[u];
    }
};
