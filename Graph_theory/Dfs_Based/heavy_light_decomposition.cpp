// Coded by Aeren(https://codeforces.com/profile/Snow-Flower)
// Modified by Ajayreddy(https://codeforces.com/profile/ajayreddy12123)
// https://github.com/Ajayreddy17/Competitive_programming/blob/main/Graph_theory/Dfs_Based/heavy_light_decomposition.cpp
// Requires graph
struct heavy_light_decomposition{
    int n;
    vector<vector<int>> adj; // stores edge ids
    vector<int> roots; // root of the component
    vector<int> pv;
    vector<int> pe;
    vector<int> size;
    vector<int> depth;
    vector<int> next; // highest point of the heavy path
    vector<int> prev; // lowest point of the heavy path
    vector<int> pos;
    vector<int> end;
    vector<int> order;
    template<class T>
    heavy_light_decomposition(const graph<T> &g, const vector<int> &roots): n(g.n), roots(roots), adj(n), pv(n, -1), pe(n, -1), size(n, 1), depth(n), next(n), prev(n), pos(n), end(n){
        iota(prev.begin(), prev.end(), 0);
        for(auto id = 0; id < (int)g.edge.size(); ++ id){
            if(g.ignore && g.ignore(id)) continue;
            auto &e = g.edge[id];
            adj[e.from].push_back(id), adj[e.to].push_back(id);
        }
        auto dfs_init = [&](auto self, int u, int root)->void{
            next[u] = root;
            if(~pe[u]) adj[u].erase(find(adj[u].begin(), adj[u].end(), pe[u]));
            for(auto &id: adj[u]){
                auto &e = g.edge[id];
                int v = u ^ e.from ^ e.to;
                pv[v] = u, pe[v] = id, depth[v] = depth[u] + 1;
                self(self, v, u);
                size[u] += size[v];
                auto &f = g.edge[adj[u][0]];
                if(size[v] > size[u ^ f.from ^ f.to]) swap(id, adj[u][0]);
            }
            if(!adj[u].empty()){
                auto &e = g.edge[adj[u][0]];
                prev[u] = prev[u ^ e.from ^ e.to];
            }
        };
        int timer = 0;
        auto dfs_hld = [&](auto self, int u)->void{
            pos[u] = timer ++;
            order.push_back(u);
            if(!adj[u].empty()){
                auto &f = g.edge[adj[u][0]];
                int hv = u ^ f.from ^ f.to;
                for(auto id: adj[u]){
                    auto &e = g.edge[id];
                    int v = u ^ e.from ^ e.to;
                    next[v] = (v == hv ? next[u] : v);
                    self(self, v);
                }
            }
            end[u] = timer;
        };
        for(auto r: roots) assert(!~pv[r]), dfs_init(dfs_init, r, r), dfs_hld(dfs_hld, r);
    }
    // O(1)
    bool ancestor_of(int u, int v) const{
        return pos[u] <= pos[v] && end[v] <= end[u];
    }
    int lca(int u, int v) const{
        for(; next[u] != next[v]; v = pv[next[v]]) if(depth[next[u]] > depth[next[v]]) swap(u, v);
        return depth[u] < depth[v] ? u : v;
    }
    int steps(int u, int v, int w = -1) const{
        return depth[u] + depth[v] - 2 * depth[~w ? w : lca(u, v)];
    }
    // f reads the position in the data structure
    // One application of f
    void access_node(int u, auto f) const{
        f(pos[u]);
    }
    // One application of f
    template<int VALS_IN_EDGES = 0>
    void access_subtree(int u, auto f) const{
        f(pos[u] + VALS_IN_EDGES, end[u]);
    }
    // f(left, right, (left->right ?))
    // O(log n) applications of f
    template<int VALS_IN_EDGES = 0>
    void access_path(int u, int v, auto f) const{
        bool dir = true;
        for(; next[u] != next[v]; v = pv[next[v]]){
            if(depth[next[u]] > depth[next[v]]) swap(u, v), dir = !dir;
            f(pos[next[v]], pos[v] + 1, dir);
        }
        if(depth[u] > depth[v]) swap(u, v), dir = !dir;
        f(pos[u] + VALS_IN_EDGES, pos[v] + 1, dir);
    }
    // Pair of indices {l, r} in the data structure. resr is reversed(v->next[v], pv[next[v]]-> ...)
    // O(log n)
    auto get_path(int u, int v) const{
        vector<pair<int, int>> resl, resr;
        access_path(u, v, [&](int l, int r, bool dir){ (dir ? resl : resr).push_back({l, r}); });
        return pair{resl, resr};
    }

    // seg(init, TT, T_ide) and segR(init, TT(r, l), T_ide)
    // T left = T_ide, right = T_ide;
    // f1(l, r) --> left = TT(left, seg.query(l, r));
    // f2(l, r) --> right   = TT(segR.query(l, r), right);
    // auto result = TT(right, left);
    void non_commutative_access_path(int u, int v, auto f1, auto f2) const{
        auto [resl, resr] = get_path(u, v);
        sort(resl.begin(), resl.end(), [&](auto l, auto r){ return depth[order[l.first]] < depth[order[r.first]]; });
        sort(resr.begin(), resr.end(), [&](auto l, auto r){ return depth[order[l.first]] < depth[order[r.first]]; });
        for (auto i = 0; i < (int) resl.size(); ++ i) f1(resl[i].first, resl[i].second);
        for (auto i = 0; i < (int) resr.size(); ++ i) f2(resr[i].first, resr[i].second);
    }
};
