std::vector<int> zet(const std::string &w){
	int n = (int)w.size();
	std::vector<int> p(n);
	int j = 0;
	for(int i=1; i < n; ++i){
		p[i] = std::max(std::min(p[j]+j-i, p[i-j]), 0);
		while(p[i]+i < n && w[p[i]] == w[p[i]+i]) p[j=i]++;
	}
	return p;
}
