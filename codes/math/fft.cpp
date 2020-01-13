typedef long double K;
typedef std::complex<K> CD;
typedef std::vector<CD> VCD;
const K PI = std::acos((K)-1);

void fft(VCD &a, bool inv=false){
	int n = (int)a.size();
	if(inv) for(CD &i : a) i = std::conj(i);
	// bit reorder
	for (int i = 1, j = 0; i < n; i++) {
		int bit = n >> 1;
		for (; j & bit; bit >>= 1) j ^= bit;
		j ^= bit;
		if(i < j) std::swap(a[i], a[j]);
	}
	for(int sz = 2; sz <= n; sz *= 2){
		CD step = CD(std::cos(PI/sz*2), std::sin(PI/sz*2));
		for(int i = 0; i < n; i += sz){
			CD w = CD(1, 0);
			for(int j = 0; j < sz/2; ++j){
				CD u = a[i+j];
				CD v = a[i+j+sz/2]*w;
				a[i+j] = u + v;
				a[i+j+sz/2] = u - v;
				w *= step;
			}
		}
	}
	if(inv) for(CD &i : a) i = std::conj(i)/CD(n, 0);
}

VCD mult(VCD a, VCD b){
	int n = 1;
	while(n < (int)std::max(a.size(), b.size())*2) n *= 2;
	a.resize(n); b.resize(n);
	fft(a); fft(b);
	VCD c(n);
	for(int i = 0; i < n; ++i) c[i] = a[i]*b[i];
	fft(c, true);
	return c;
}

template <typename T>
VCD to_complex(std::vector<T> vec){
	VCD ret;
	for(T &i : vec) ret.push_back(CD(i, 0));
	return ret;
}
template <typename T>
std::vector<T> to_type(VCD vec){
	std::vector<T> ret;
	for(CD &i : vec) ret.push_back((T)std::round(i.real()));
	return ret;
}
