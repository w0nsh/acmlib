using namespace std;

#define ll long long 
#define pb push_back
#define f first
#define s second
const ll INF = 1e9 + 7;

template< class T > using pqg = priority_queue< T, vector< T >, greater< T > >;
template< class T > T poll(pqg< T > & x){
    T y = x.top(); x.pop();
    return y;
}
template<int SZ> struct mcf{
    struct Edge{int v, rev; ll flow, cap, cost;};
    vector<Edge> adj[SZ];
    void addEdge(int u, int v, ll cap, ll cost){
        Edge a{v, adj[v].size(), 0, cap, cost}, b{u, adj[u].size(), 0, 0, -cost};
        adj[u].pb(a), adj[v].pb(b);
    }
    int ST, EN;
    pair<int, int> pre[SZ];
    pair<ll, ll> cost[SZ];
    ll totFlow, totCost, curCost;
    void reweight(){
    	for(int i = 0 ; i < SZ; i++)
    	 	for(auto & p : adj[i])
    	 		p.cost += cost[i].f - cost[p.v].f;
    }
    bool spfa(){
        for(int i = 0; i < SZ; i++) cost[i] = {INF, 0};
        cost[ST] = {0, INF};
        pqg< pair< ll, int > > todo; todo.push({0, ST});
        while(todo.size()){
            auto x = poll(todo);
            if(x.f > cost[x.s].f) continue;
            for(auto & a : adj[x.s]) if(x.f + a.cost < cost[a.v].f && a.flow < a.cap){
                pre[a.v] = {x.s, a.rev};
                cost[a.v] = {x.f + a.cost, min(a.cap - a.flow, cost[x.s].s)};
                todo.push({cost[a.v].f, a.v});
            }
        }
        curCost += cost[EN].f;
        return cost[EN].s;
    }
    void backtrack(){
        auto f = cost[EN].s; totFlow += f, totCost += curCost*f;
        for (int x = EN; x != ST; x = pre[x].f){
            adj[x][pre[x].s].flow -= f;
            adj[pre[x].f][adj[x][pre[x].s].rev].flow += f;
        }
    }
    pair<ll, ll> minCostFlow(int _ST, int _EN) {
        ST = _ST, EN = _EN; totFlow = totCost = curCost = 0;
        spfa();
        while (1) {
            reweight();
            if (!spfa()) return {totFlow, totCost};
            backtrack();
        }
    }
};