template<class T>
struct graph{
    struct E{
        int from, to;
        T cost;
    };
    int n;
    vector<E> edge;
    vector<vector<int>> adj;
    function<bool(int)> ignore;
    graph(int n = 1): n(n), adj(n){
        assert(n >= 1);
    }
    graph(const vector<vector<int>> &adj, bool undirected = true): n((int)adj.size()), adj(n){
        assert(n >= 1);
        if(undirected){
            for(auto u = 0; u < n; ++ u) for(auto v: adj[u]) if(u < v) link(u, v);
        }
        else for(auto u = 0; u < n; ++ u) for(auto v: adj[u]) orient(u, v);
    }
    graph(const vector<vector<pair<int, T>>> &adj, bool undirected = true): n((int)adj.size()), adj(n){
        assert(n >= 1);
        if(undirected){
            for(auto u = 0; u < n; ++ u) for(auto [v, w]: adj[u]) if(u < v) link(u, v, w);
        }
        else for(auto u = 0; u < n; ++ u) for(auto [v, w]: adj[u]) orient(u, v, w);
    }
    graph(int n, vector<array<int, 2>> &edge, bool undirected = true): n(n), adj(n){
        assert(n >= 1);
        for(auto [u, v]: edge) undirected ? link(u, v) : orient(u, v);
    }
    graph(int n, vector<tuple<int, int, T>> &edge, bool undirected = true): n(n), adj(n){
        assert(n >= 1);
        for(auto [u, v, w]: edge) undirected ? link(u, v, w) : orient(u, v, w);
    }
    int operator()(int u, int id) const{
#ifndef ONLINE_JUDGE
        assert(0 <= id && id < (int)edge.size());
        assert(edge[id].from == u || edge[id].to == u);
#endif
        return u ^ edge[id].from ^ edge[id].to;
    }
    int link(int u, int v, T w = {}){ // insert an undirected edge
        int id = (int)edge.size();
        adj[u].push_back(id), adj[v].push_back(id), edge.push_back({u, v, w});
        return id;
    }
    int orient(int u, int v, T w = {}){ // insert a directed edge
        int id = (int)edge.size();
        adj[u].push_back(id), edge.push_back({u, v, w});
        return id;
    }
    graph transposed() const{ // the transpose of the directed graph
        graph res(n);
        for(auto &e: edge) res.orient(e.to, e.from, e.cost);
        res.ignore = ignore;
        return res;
    }
    int degree(int u) const{ // the degree (outdegree if directed) of u (without the ignoration rule)
        return (int)adj[u].size();
    }
    // The adjacency list is sorted for each vertex.
    vector<vector<int>> get_adjacency_list() const{
        vector<vector<int>> res(n);
        for(auto u = 0; u < n; ++ u) for(auto id: adj[u]){
                if(ignore && ignore(id)) continue;
                res[(*this)(u, id)].push_back(u);
            }
        return res;
    }
    void set_ignoration_rule(const function<bool(int)> &f){
        ignore = f;
    }
    void reset_ignoration_rule(){
        ignore = nullptr;
    }
    friend ostream &operator<<(ostream &out, const graph &g){
        for(auto id = 0; id < (int)g.edge.size(); ++ id){
            if(g.ignore && g.ignore(id)) continue;
            auto &e = g.edge[id];
            out << "{" << e.from << ", " << e.to << ", " << e.cost << "}\n";
        }
        return out;
    }
};
