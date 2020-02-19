// 1-based indexing
struct Matching{
	static const int INF = 1000000666;
	int n;
	std::vector<std::vector<int> > g;
	std::vector<int> match, col, U, dist;
	Matching(){}
	Matching(int N){
		n = N;
		g = std::vector<std::vector<int> >(n+1);
		match = col = dist = std::vector<int>(n+1);
	}
	void add_edge(int a, int b){
		g[a].push_back(b); g[b].push_back(a);
	}
	void color(int v, int c){
		if((col[v] = c) == 1) U.push_back(v);
		for(auto ch : g[v]) if(!col[ch]) color(ch, (c == 1 ? 2 : 1));
	}
	bool bfs(){
		std::queue<int> que;
		for(auto u : U)
			if(!match[u]) dist[u] = 0, que.push(u);
			else dist[u] = INF;
		dist[0] = INF;
		while(!que.empty()){
			int u = que.front(); que.pop();
			if(dist[u] < dist[0]) for(auto v : g[u]) if(dist[match[v]] == INF)
				dist[match[v]] = dist[u] + 1, que.push(match[v]);
		}
		return dist[0] != INF;
	}
	bool dfs(int u){
		if(!u) return true;
		for(auto v : g[u]) if(dist[match[v]] == dist[u] + 1 && dfs(match[v]))
				return match[v] = u, match[u] = v;
		return dist[u] = INF, false;
	}
	int max_matching(){
		for(int i = 1; i <= n; ++i) if(!col[i]) color(i, 1);
		int ret = 0;
		while(bfs()) for(auto u : U) if(!match[u] && dfs(u)) ret++;
		return ret;
	}
};
