struct Dinic{
	struct Edge{
		int from, to, cap, flow;
		Edge(){}
		Edge(int u, int v, int c, int f) : from(u), to(v), cap(c), flow(f) {}
	};
	const int INF = 1e9+7; // zmien jezeli long longi
	std::vector<Edge> edges;
	std::vector<std::vector<int> > g;
	std::vector<bool> vis;
	std::vector<int> d, cur;
	Dinic(){}
	Dinic(int n){
		edges = std::vector<Edge>();
		vis = std::vector<bool>(n);
		d = cur = std::vector<int>(n);
		g = std::vector<std::vector<int> >(n);
	}
	void add_edge(int from, int to, int cap){
		edges.push_back(Edge(from, to, cap, 0));
		edges.push_back(Edge(to, from, 0, 0));
		int t_m = (int)edges.size();
		g[from].push_back(t_m-2);
		g[to].push_back(t_m-1);
	}
	bool bfs(int s, int t){
		std::fill(vis.begin(), vis.end(), false);
		std::queue<int> q;
		q.push(s);
		d[s] = 0; vis[s] = 1;
		while(!q.empty()){
			int x = q.front(); q.pop();
			for(int i = 0; i < (int)g[x].size(); ++i){
				Edge &e = edges[g[x][i]];
				if(!vis[e.to] && e.cap > e.flow){
					vis[e.to] = 1;
					d[e.to] = d[x]+1;
					q.push(e.to);
				}
			}
		}
		return vis[t];
	}
 	int dfs(int x, int a, int s, int t){
		if(x == t || a == 0) return a;
		int flow  = 0, _f;
		for(int& i = cur[x]; i < (int)g[x].size(); ++i){
			Edge& e = edges[g[x][i]];
			if(d[x]+1 == d[e.to] && (_f = dfs(e.to, std::min(a, e.cap - e.flow), s, t)) > 0){
				e.flow += _f;
				edges[g[x][i]^1].flow -= _f;
				flow += _f;
				a -= _f;
				if(a == 0) break;
			}
		}
		return flow;
	}
	int max_flow(int s, int t){
		int flow = 0;
		while(bfs(s, t)){
			std::fill(cur.begin(), cur.end(), 0);
			flow += dfs(s, INF, s, t);
		}
		return flow;
	}
};
