template<class T>
struct BIT2D{
	int sz;
	std::vector<T> t;
	inline int LSB(int a){ return a&(-a); }
	BIT2D(){}
	BIT2D(int s){
		sz = s+1;
		t.resize(sz*sz);
	}
	void add(int x, int y, T val){
		x++; y++;
		while(x < sz){
			int c = y;
			while(c < sz) t[x*sz+c] += val, c += LSB(c); // change operation here
			x += LSB(x);
		}
	}
	T query(int x, int y){
		x++; y++;
		T r = 0;
		while(x > 0){
			int c = y;
			while(c > 0) r += t[x*sz+c], c -= LSB(c); // change operation here
			x -= LSB(x);
		}
		return r;
	}
};
