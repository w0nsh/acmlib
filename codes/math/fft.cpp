typedef long double K;
typedef std::complex<K> CD;
typedef std::vector<CD> VCD;
const K PI = std::acos((K)-1);

void fft(VCD &vec){
	int n = (int)vec.size();
	if(n == 1) return;
	VCD even, odd;
	even.reserve(n/2);
	odd.reserve(n/2);
	for(int i = 0; i < n; ++i) (i%2 == 0 ? even.push_back(vec[i]) : odd.push_back(vec[i]));
	fft(even);
	fft(odd);
	CD step = CD(std::cos(PI/n*2), std::sin(PI/n*2));
	CD w = CD(1, 0);
	for(int i = 0; i < n/2; ++i){
		vec[i] = even[i] + w*odd[i];
		vec[i+n/2] = even[i] - w*odd[i];
		w = w*step;
	}
}

void ifft(VCD &vec){
	int n = (int)vec.size();
	for(CD &i : vec) i = std::conj(i);
	fft(vec);
	for(CD &i : vec) i = std::conj(i)/CD(n, 0);
}

VCD mult(VCD a, VCD b){
	int n = 1;
	while(n < (int)std::max(a.size(), b.size())*2) n *= 2;
	a.resize(n); b.resize(n);
	fft(a); fft(b);
	VCD c(n);
	for(int i = 0; i < n; ++i) c[i] = a[i]*b[i];
	ifft(c);
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
