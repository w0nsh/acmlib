typedef std::pair<int, int> PII;

int side(PII a, PII b, PII c){
	PII x = std::make_pair(b.first-a.first, b.second-a.second);
	PII y = std::make_pair(c.first-a.first, c.second-a.second);
	if(1ll*x.first*y.second-1ll*x.second*y.first > 0) return 1;
	else if(1ll*x.first*y.second-1ll*x.second*y.first == 0) return 0;
	return -1;
}
 
std::vector<PII> hull(std::vector<PII> vec){
	std::sort(vec.begin(), vec.end());
	std::vector<PII> ret;
	ret.push_back(vec[0]);
	for(int i = 1; i < (int)vec.size(); ++i){
		while((int)ret.size() >= 2 && side(ret[(int)ret.size()-2], ret.back(), vec[i]) >= 0) ret.pop_back(); // change to > for all points on hull
		ret.push_back(vec[i]);
	}
	int old = (int)ret.size();
	for(int i = (int)vec.size()-2; i >= 0; --i){
		while((int)ret.size() > old && side(ret[(int)ret.size()-2], ret.back(), vec[i]) >= 0) ret.pop_back(); // change to > for all points on hull
		ret.push_back(vec[i]);
	}
	ret.pop_back();
	return ret;
}
