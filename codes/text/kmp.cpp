// pi[i] = lps of prefix of length i
std::vector<int> calc_pi(const std::string &s){
	std::vector<int> pi(s.size()+1);
	int b;
	pi[0] = b = -1;
	for(int i = 1; i <= (int)s.size(); i++){
		while((b > -1) && (s[b] != s[i - 1])) b = pi[b];
		pi[i] = ++b;
	}
	return pi;
}

// match[i] = is there a match starting at s[i]
std::vector<bool> find(const std::string &w, const std::string &s){
	std::vector<bool> match(s.size());
	std::vector<int> pi = calc_pi(w);
	int b = 0, m = (int)w.size();
	for(int i = 0; i < (int)s.size(); ++i){
		while((b > -1) && (w[b] != s[i])) b = pi[b];
		if(++b == m) match[i-m+1] = true, b = pi[b];
	}
	return match;
}
