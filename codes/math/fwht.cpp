// or      inv
// [1 1]   [0 1]
// [1 0]   [1 -1]
void transform(std::vector<int> &a, bool inv=false){
	int n = (int)a.size();
	for(int sz = 1; sz < n; sz *= 2){
		for(int i = 0; i < n; i += sz*2){
			for(int j = i; j < i+sz; ++j){
				int u = a[j], v = a[j+sz];
				if(!inv) a[j] = u+v, a[j+sz] = u;
				else a[j] = v, a[j+sz] = u-v;
			}
		}
	}
}

// xor         inv
// [1 1]    1/2 * [1 1]
// [1 -1]         [1 -1]
