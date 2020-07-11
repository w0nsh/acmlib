// Marcin Knapik
#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 7;

int n, R, czas;
vector<int> G[N], tree[N], rev_G[N], pdom_rev[N];
int pdom[N], T[N], bdom[N], dsu[N], mini[N], pre[N], rev[N];

namespace dominator{
	void prepare(){
		czas = 0;
		for(int i = 1; i <= n; i++){
			rev_G[i].clear();
			tree[i].clear();
			pdom_rev[i].clear();
			pre[i] = 0;
		}
	}

	int Find(int u, int x = 0){
		if(u == dsu[u])
			return x ? -1 : u;
		int v = Find(dsu[u], x + 1);
		if(v == -1)
			return u;
		if(pdom[mini[dsu[u]]] < pdom[mini[u]])
			mini[u] = mini[dsu[u]];
		dsu[u] = v;
		return x ? v : mini[u];
	}

	void Union(int u,int v){
		dsu[v] = u;   
	}

	void dfs(int x){
		czas++;
		pre[x] = czas, rev[czas] = x;
		pdom[czas] = bdom[czas] = mini[czas] = dsu[czas] = czas;

		for(int & u : G[x]){
			if(!pre[u]){
				dfs(u);
				T[pre[u]] = pre[x];
			}
			rev_G[pre[u]].push_back(pre[x]);
		}
	}

	void create_dominator_tree(){
		// You have to have correct graph G,
		// parameter n - (number of verticies
		// 1 - indexed), and root R
			
		prepare(); // If you deal with multiple testcases
		dfs(R);

		for(int i = czas; i >= 1; i--){
			for(int u : rev_G[i])
				pdom[i] = min(pdom[i], pdom[Find(u)]);
			if(i > 1)
				pdom_rev[pdom[i]].push_back(i);
			for(int w : pdom_rev[i]){
				int v = Find(w);
				if(pdom[v] == pdom[w])
					bdom[w] = pdom[w];
				else 
					bdom[w] = v;
			}
			if(i > 1)
				Union(T[i], i);
		}
		for(int i = 2; i <= czas; i++){
			if(bdom[i] != pdom[i])
				bdom[i] = bdom[bdom[i]];
			tree[rev[i]].push_back(rev[bdom[i]]);
			tree[rev[bdom[i]]].push_back(rev[i]);
		}
	}
}
