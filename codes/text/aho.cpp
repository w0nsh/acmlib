#include<bits/stdc++.h>
using namespace std;

#define sz(s) (int)s.size()
#define f first
#define s second
#define all(x) x.begin(), x.end()
#define pb push_back

const int K = 62;

int lit(char x){
	if(x >= 'a' && x <= 'z')
		return x-'a';
	if(x >= 'A' && x <= 'Z')
		return x-'A'+26;
	return x-'0'+52;
}

struct Vertex {
    int next[K];
    int leaf = -1;
    int p = -1;
    char pch;
    int link = -1;
    int go[K];
    
    // moje wlasne
    bool vis = false;
    vector<int> ktore;

    Vertex(int _p=-1, char ch='$') : p(_p), pch(ch) {
        fill(begin(next), end(next), -1);
        fill(begin(go), end(go), -1);
    }
};

vector<Vertex> t(1);

void add_string(string const& s, int id) {
    int v = 0;
    for (char ch : s) {
        int c = lit(ch);
        if (t[v].next[c] == -1) {
            t[v].next[c] = t.size();
            t.emplace_back(v, ch);
        }
        v = t[v].next[c];
    }
    t[v].ktore.pb(id);
    t[v].leaf = id;
}

int go(int v, char ch);

int get_link(int v) {
    if (t[v].link == -1) {
        if (v == 0 || t[v].p == 0)
            t[v].link = 0;
        else
            t[v].link = go(get_link(t[v].p), t[v].pch);
    }
    return t[v].link;
}

int go(int v, char ch) {
    int c = lit(ch);
    if (t[v].go[c] == -1) {
        if (t[v].next[c] != -1)
            t[v].go[c] = t[v].next[c];
        else
            t[v].go[c] = v == 0 ? 0 : go(get_link(v), ch);
    }
    return t[v].go[c];
} 

void add_current(vector<int>&ret, int v){
	if(t[v].vis)
		return;
	t[v].vis = true;
	for(auto&u:t[v].ktore)
		ret.pb(u);
	add_current(ret, get_link(v));
}

vector< int > ktore_wystepowaly(string w){
	vector<int> ret;
	int v = 0;
	
	for(int i = 0; i < sz(w); i++){
		v = go(v, w[i]);
		add_current(ret, v);	
	}
	return ret; 
}
const int N = 1001;

int good[N];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);

	string w;
	cin >> w;
	int n;
	cin >> n;

	for(int i =0; i < n; i++){
		string temp;
		cin >> temp;
		
		add_string(temp, i);
	}
	
	vector<int> odp = ktore_wystepowaly(w);
	for(auto&u:odp)
		good[u] = 1;
	for(int i = 0; i < n; i++){
		if(good[i])
			cout << "Y\n";
		else
			cout << "N\n";
	}	
}
