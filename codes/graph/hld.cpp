using namespace std;

const int N=1e5+5;
const int M=1<<17;

int n;
vector<int> G[N];

namespace hld{
	int sz[N], par[N], in[N], nxt[N], tree[M*2+5], tim;
	void sz_dfs(int v=1, int p=-1){
		sz[v]=1, par[v]=p;
		for(auto &u: G[v]){
			if(u==p) continue;
			sz_dfs(u, v);
			sz[v]+=sz[u];
			if(G[v][0]==par[v] || sz[u]>sz[G[v][0]]) swap(u, G[v][0]);
		}
	}
	void hld_dfs(int v=1){
		in[v]=++tim;
		for(auto &u: G[v]){
			if(u==par[v]) continue;
			nxt[u]=(u==G[v][0] ? nxt[v] : u);
			hld_dfs(u);
		}
	}
	void init(int root=1){
		sz_dfs(root);
		hld_dfs(root);
	}
	int query(int l, int r){
		int ret=-1e9;
		l+=M, r+=M;
		while(l<=r){
			if(l&1) ret=max(ret, tree[l++]);
			if(!(r&1)) ret=max(ret, tree[r--]);
			l>>=1, r>>=1;
		}
		return ret;
	}
	void add(int l, int val){
		l+=M, tree[l]+=val, l>>=1;
		while(l) tree[l]=max(tree[l*2], tree[l*2+1]), l>>=1;
	}
	int path(int v, int u){
		int ret=-1e9;
		while(nxt[v]!=nxt[u]){
			if(in[v]>in[u]) swap(v, u);
			ret=max(ret, query(in[nxt[u]], in[u]));
			u=par[nxt[u]];
		}
		if(in[v]>in[u]) swap(v, u);
		ret=max(ret, query(in[v], in[u])); //in[v]+1 if you work on edges
		return ret;
	}
	//query(in[v], in+sz[v]-1) if you want to query on subtree
}
