struct Gauss{
	// moze sie wywalac jak modulo nie jest pierwsze
	vector<int> solve(vector<vector<int>> eq, ll mod){
		auto fast = [&](ll a, ll b){
			ll ret = 1;
			while(b){
				if(b&1)
					(ret *= a) %= mod;
				(a*=a)%=mod;
				b>>=1;
			}
			return ret%mod;
		};
		auto mnoz = [&](vi& vec, ll skal){
			for(auto&u: vec)
				(u *= skal) %= mod;
		};
		auto odejmij = [&](vi&vec1, vi&vec2){
			for(int i=0; i<sz(vec1); i++)
				vec1[i] = ((vec1[i] - vec2[i])%mod + mod)%mod;
		};
		int kol = sz(eq[0])-1;
		int wie = sz(eq);
		if(kol == 0 || wie == 0)
			return {};
		while(wie<kol){
			vi lel(kol+1, 0);
			eq.pb(lel);
			wie++;
		}
		for(int i = 0; i<kol; i++){
			int nr = -1;
			for(int j=i; j<wie; j++)
				if(eq[j][i] != 0){
					nr = j;
					break;
				}
			if(nr == -1)
				continue;
			swap(eq[i], eq[nr]);
			for(int j=i+1; j<wie; j++)
				if(eq[j][i]!=0){
					mnoz(eq[j], fast(eq[i][i], mod-2));
					odejmij(eq[j], eq[i]);
				}
		}
		vi ret;
		for(int i = kol-1; i>=0; i--){
			if(eq[i][i] == 0){
				if(eq[i][kol] == 0)
					eq[i][i] = 1%mod;
				else
					return {};
			}
			mnoz(eq[i], fast(eq[i][i], mod-2));
			ret.pb(eq[i][kol]);
			for(int j=i-1; j>=0; j--)
				if(eq[j][i]!=0){
					mnoz(eq[j], fast(eq[j][i], mod-2));
					odejmij(eq[j], eq[i]);
				}
		}
		reverse(all(ret));
		return ret;
	}
};