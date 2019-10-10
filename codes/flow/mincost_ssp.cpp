#include <bits/stdc++.h>
#define FOR(i, n) for(int i = 0; i < (n); ++i)
#define REP(i, a, b) for(int i = (a); i < (b); ++i)
#define TRAV(i, n) for(auto &i : n)
#define SZ(x) (int)(x).size()
#define PR std::pair
#define MP std::make_pair
#define X first
#define Y second
typedef long long ll;
typedef std::pair<int, int> PII;
typedef std::vector<int> VI;

struct MCMF{
	const static int INF = 1000000666;
	const static ll LINF = 1000000000ll*1000000000ll+666ll;
	struct Edge{
		int v, cap;
		ll cost, origcost;
		Edge *back;
		Edge(){}
		Edge(int to, int cp, ll cst) : v(to), cap(cp), cost(cst), origcost(cst), back(nullptr) {}
	};
	int n, src, sink;
	std::vector<std::vector<Edge*> > g;
	void reset(int sz, int s, int e){
		src = s;
		sink = e;
		n = sz;
		g = std::vector<std::vector<Edge*> >(n);
	}
	void add_edge(int a, int b, int cap, int cost){
		g[a].push_back(new Edge(b, cap, cost));
		g[b].push_back(new Edge(a, 0, 0));
		g[a].back()->back = g[b].back();
		g[b].back()->back = g[a].back();
	}
	void build(const std::vector<std::vector<PR<int, PII> > > &graph, int s, int e){
		reset(SZ(graph), s, e);
		FOR(i, n) TRAV(j, graph[i]) add_edge(i, j.X, j.Y.X, j.Y.Y);
	}
	void calc_price_bellman(std::vector<ll> &price){
		std::fill(price.begin(), price.end(), LINF);
		price[src] = 0;
		FOR(_, n) FOR(i, n) TRAV(e, g[i])
			if(e->cap > 0 && price[i] + e->cost < price[e->v]) price[e->v] = price[i] + e->cost;
		// negative cycle
		FOR(i, n) TRAV(e, g[i]) if(e->cap > 0 && price[i] + e->cost < price[e->v]) assert(false);
	}
	// TODO
	// for positive edges
	// void calc_price_dijkstra(std::vector<ll> &price){}
	int find_path(){
		std::priority_queue<PR<ll, int> > que;
		std::vector<ll> price(n, LINF);
		std::vector<PR<Edge*, int> > parent(n, MP(nullptr, -1));
		que.push(MP(0, src));
		price[src] = 0;
		while(!que.empty()){
			int cur = que.top().Y;
			que.pop();
			TRAV(e, g[cur]){
				if(e->cap == 0) continue;
				assert(e->cost >= 0); // debug
				if(price[cur] + e->cost < price[e->v]){
					price[e->v] = price[cur] + e->cost;
					parent[e->v] = MP(e, cur);
					que.push(MP(-price[e->v], e->v));
				}
			}
		}
		if(parent[sink].Y == -1) return 0;
		FOR(i, n) TRAV(e, g[i]) if(e->cap > 0){
			e->cost = e->cost + price[i] - price[e->v];
			e->back->cost = 0; // TODO: is it needed?
		}
		auto cur = parent[sink];
		int min = INF;
		while(cur.Y != -1){
			min = std::min(min, cur.X->cap);
			cur = parent[cur.Y];
		}
		cur = parent[sink];
		while(cur.Y != -1){
			cur.X->cap -= min;
			cur.X->back->cap += min;
			cur = parent[cur.Y];
		}
		return min;
	}
	PR<ll, int> mcmf(){
		std::vector<ll> price(n);
		calc_price_bellman(price);
		FOR(i, n) TRAV(e, g[i]) if(e->cap > 0) e->cost = e->cost + price[i] - price[e->v];
		int flow = 0;
		while(true){
			int cur = find_path();
			if(cur == 0) break;
			flow += cur;
		}
		ll cost = 0;
		FOR(i, n) TRAV(e, g[i]) cost += e->origcost*(e->back->cap);
		return MP(cost, flow);
	}
};

int main(){
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	
	return 0;
}
