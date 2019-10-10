// sh - parzystosc
// 0 - parzyste, 1 - nieparzyste
// aaaa -> 0 -> [0, 1, 2, 1]   1 -> [1, 2, 2, 1]
std::vector<int> manacher(const std::string &w, int sh){
	sh = 1-sh;
	int n = (int)w.size();
	std::vector<int> p(n);
	int g = 0;
	p[0] = 1-sh;
	for(int i=1;i<n;++i){
		if(2*g-i>=0) p[i] = std::max(std::min(p[2*g-i], p[g]+g-i), 0);
		else p[i] = 0;
		while(i-p[i]-sh >= 0 && i+p[i]<n && w[i+p[i]] == w[i-p[i]-sh]) p[g=i]++;
	}
	return p;
}
