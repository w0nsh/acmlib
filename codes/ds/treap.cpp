#include <bits/stdc++.h>
#define FOR(i, n) for(int i = 0; i < (n); ++i)
#define REP(i, a, b) for(int i = (a); i < (b); ++i)
#define TRAV(i, n) for(auto &i : n)
#define SZ(x) (int)(x).size()
#define PR std::pair
#define MP std::make_pair
#define X first
#define Y second
typedef long long ll;
typedef std::pair<int, int> PII;
typedef std::vector<int> VI;

const int INF = 1000000666;
struct Node{
	int prio, val, cnt, mx;
	ll sum, add;
	bool rev;
	Node *l, *r;
	Node(int v) : prio(rand()), val(v), cnt(1), mx(v), sum(v), add(0), rev(false), l(nullptr), r(nullptr) {}
};
int get_cnt(Node *t){ return t ? t->cnt : 0; }
int get_mx(Node *t){ return t ? t->mx : -INF; }
ll get_sum(Node *t){ return t ? t->sum : 0; }

void push(Node *t){
	if(t){
		if(t->rev){
			t->rev = false;
			std::swap(t->l, t->r);
			if(t->l) t->l->rev ^= true;
			if(t->r) t->r->rev ^= true;	
		}
		if(t->add){
			t->val += t->add;
			t->mx += t->add;
			t->sum += t->add*t->cnt;
			if(t->l) t->l->add += t->add;
			if(t->r) t->r->add += t->add;
			t->add = 0;
		}
	}
}

void upd_cnt(Node *t){ if(t) t->cnt = get_cnt(t->l) + get_cnt(t->r) + 1; }
void upd_sum(Node *t){ if(t) t->sum = get_sum(t->l) + get_sum(t->r) + t->val; }
void upd_mx(Node *t){ if(t) t->mx = std::max(t->val, std::max(get_mx(t->l), get_mx(t->r))); }
void upd(Node *t){ if(t) push(t->l), push(t->r); upd_cnt(t); upd_sum(t); upd_mx(t); }

void merge(Node * &t, Node *l, Node *r){
	push(l); push(r);
	if(!l || !r) t = l ? l : r;
	else if(l->prio > r->prio) merge(l->r, l->r, r), t = l;
	else merge(r->l, l, r->l), t = r;
	upd(t);
}

// key - pos in array 0 indexed
void split(Node *t, Node * &l, Node * &r, int key, int add = 0){
	if(!t) l = r = nullptr;
	else{
		push(t);
		int cur_key = add + get_cnt(t->l);
		if(key <= cur_key) split(t->l, l, t->l, key, add), r = t;
		else split(t->r, t->r, r, key, add + 1 + get_cnt(t->l)), l = t;
		upd(t);
	}
}

void insert(Node * &t, int pos, int val){
	Node *el = new Node(val);
	Node *t1, *t2; split(t, t1, t2, pos);
	merge(t1, t1, el); merge(t, t1, t2);
}

void remove(Node * &t, int pos){
	push(t);
	if(get_cnt(t->l) == pos){
		Node *ret;
		merge(ret, t->l, t->r);
		delete t;
		t = ret;
	}else if(get_cnt(t->l) > pos) remove(t->l, pos);
	else remove(t->r, pos-get_cnt(t->l)-1);
	upd(t);
}

void reverse(Node * &t, int l, int r){
	Node *t1, *t2, *t3; split(t, t1, t2, l); split(t2, t2, t3, r-l+1);
	t2->rev ^= true;
	merge(t, t1, t2); merge(t, t, t3);
}

void add(Node * &t, int l, int r, int val){
	Node *t1, *t2, *t3; split(t, t1, t2, l); split(t2, t2, t3, r-l+1);
	t2->add += val;
	merge(t, t1, t2); merge(t, t, t3);
}

ll get_sum(Node * &t, int l, int r){
	Node *t1, *t2, *t3; split(t, t1, t2, l); split(t2, t2, t3, r-l+1);
	ll ret = t2->sum;
	merge(t, t1, t2); merge(t, t, t3);
	return ret;
}

int get_mx(Node * &t, int l, int r){
	Node *t1, *t2, *t3; split(t, t1, t2, l); split(t2, t2, t3, r-l+1);
	int ret = t2->mx;
	merge(t, t1, t2); merge(t, t, t3);
	return ret;
}

int main(){
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	
	return 0;
}
