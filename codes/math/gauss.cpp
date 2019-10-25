namespace Gauss{
	const int MOD = 1000000007; // 2*MOD < zakres
	int modpow(int a, int e){
		int ret = 1;
		while(e > 0){ if(e&1) ret = (1ll*ret*a)%MOD; a = (1ll*a*a)%MOD; e >>= 1; }
		return ret;
	}
	// 0 - nie ma rozwiazan, 1 - jedno rozwiazanie, 2 - nieskonczenie wiele rozwiazan
	int solve(std::vector<std::vector<int> > a, std::vector<int> & ans){
		int n = (int)a.size(); assert(n > 0);
		int m = (int)a[0].size()-1; assert(m > 0);
		std::vector<int> where (m, -1);
		for(int col = 0, row = 0; col < m && row < n; ++col){
			if(a[row][col] == 0) continue;
			where[col] = row;
			for(int i = 0; i < n; ++i) if(i != row) {
				int c = (1ll*a[i][col]*modpow(a[row][col], MOD-2))%MOD;
				for(int j = col; j <= m; ++j) a[i][j] = ((1ll*a[i][j] - 1ll*a[row][j]*c)%MOD+MOD)%MOD;
			}
			++row;
		}
		ans.assign(m, 0);
		for(int i = 0; i < m; ++i) if(where[i] != -1) ans[i] = (1ll*a[where[i]][m]*modpow(a[where[i]][i], MOD-2))%MOD;
		for(int i = 0; i < n; ++i){
			int sum = 0;
			for(int j = 0; j < m; ++j) sum = (1ll*sum+ 1ll*ans[j]*a[i][j])%MOD;
			if(sum != a[i][m]) return 0;
		}
		for(int i = 0; i < m; ++i) if(where[i] == -1) return 2;
		return 1;
	}
}
