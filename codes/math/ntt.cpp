const int MOD = 998244353; // 2 * 2 * ... * 2 * 7 * 17
int R;

int modpow(int a, int e){
	int ret = 1;
	while(e > 0){
		if(e&1) ret = (1ll*ret*a)%MOD;
		a = (1ll*a*a)%MOD;
		e >>= 1;
	}
	return ret;
}

//CALL THIS FIRST
void findr(){
	R = -1;
	int i = 2;
	while(R == -1){
		if(modpow(i, (MOD-1)/2) != 1 &&
			modpow(i, (MOD-1)/7) != 1 &&
			modpow(i, (MOD-1)/17) != 1){
				R = i;
				break;
			}
		i++;
	}
	assert(R!=-1);
}

void ntt(std::vector<int> &a, bool inv=false){
	int n = (int)a.size();
	// bit reorder
	for (int i = 1, j = 0; i < n; i++) {
		int bit = n >> 1;
		for (; j & bit; bit >>= 1) j ^= bit;
		j ^= bit;
		if(i < j) std::swap(a[i], a[j]);
	}
	for(int sz = 2; sz <= n; sz *= 2){
		int c = (MOD-1)/sz;
		int step = modpow(R, c);
		if(inv) step = modpow(step, MOD-2);
		for(int i = 0; i < n; i += sz){
			int w = 1;
			for(int j = 0; j < sz/2; ++j){
				int u = a[i+j];
				int v = (1ll*a[i+j+sz/2]*w)%MOD;
				a[i+j] = u + v < MOD ? u + v : u + v - MOD;
				a[i+j+sz/2] = u - v >= 0 ? u - v : u - v + MOD;
				w = (1ll*w*step)%MOD;
			}
		}
	}
	if(inv){
		int odw = modpow(n, MOD-2);
		for(auto &i : a) i = (1ll*i*odw)%MOD;
	}
}
struct Poly{
	std::vector<int> c;
	Poly(){}
	Poly(std::vector<int> v) : c(v) {}
	int size(){
		return (int)c.size();
	}
	// a *= b
	void operator *=(Poly b){
		assert(b.size() == this->size());
		int n = b.size();
		for(int i = 0; i < n; ++i) b.c.push_back(0), this->c.push_back(0);
		ntt(this->c);
		ntt(b.c);
		for(int i = 0; i < (int)b.c.size(); ++i) this->c[i] = (1ll*this->c[i]*b.c[i])%MOD;
		ntt(this->c, true);
	}
};

std::ostream &operator <<(std::ostream &s, Poly &p){
	s << "[";
	for(int i = 0; i < (int)p.c.size(); ++i){
		if(i != 0) s << " ";
		s << p.c[i];
	}
	s << "]";
	return s;
}
