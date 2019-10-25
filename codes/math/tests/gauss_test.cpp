#include<bits/stdc++.h>
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

////////////////////
//gauss.cpp
////////////////////

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

std::mt19937 _gen;
std::uniform_int_distribution<int> _u_i_d(0, 1<<30);
inline int los(int a, int b){
	return a + _u_i_d(_gen)%(b-a+1);
}

int main(){
	_gen.seed(std::chrono::steady_clock::now().time_since_epoch().count());
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	int N = los(1, 100);
	int test = 1;
	while(true){
		std::cout << "Test " << test++ << std::endl;
		int n = los(1, N);
		int m = los(1, N);
		n = 500;
		m = 500;
		std::vector<VI> vec(n);
		FOR(i, n){
			FOR(j, m) vec[i].push_back(los(0, 1000));
			vec[i].push_back(los(0, 1000));
		}
		VI ans;
		int rzw = Gauss::solve(vec, ans);
		if(rzw == 0) std::cout << "No solution" << std::endl;
		else{
			assert(SZ(ans) == m);
			std::cout << "Solution found(" << rzw << ")" << "\nchecking... " << std::flush;
			bool bad = false;
			FOR(i, n){
				int have = 0;
				FOR(j, m) have = (1ll*have+1ll*vec[i][j]*ans[j])%Gauss::MOD;
				if(have != vec[i].back()) bad = true;
			}
			if(!bad) std::cout << "OK" << std::endl;
			else{
				std::cout << "Wrong solution\n";
				std::cout << n << " " << m << "\n";
				FOR(i, n){
					FOR(j, m){
						std::cout << vec[i][j] << " ";
					}
					std::cout << " " << vec[i].back();
					std::cout << "\n";
				}
				std::cout << "Solution:\n";
				FOR(i, m) std::cout << ans[i] << " ";
				std::cout << std::endl;
				break;
			}
		}
	}
	return 0;
}
