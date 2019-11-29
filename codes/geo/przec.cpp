#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define f first
#define s second
#define pb push_back
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define ld long double
#define MP make_pair
const ld EPS = 1e-12;

struct pt {
    ld x, y;
};

struct seg {
    pt p, q;
    int id;

    ld get_y(ld x) const {
        if (abs(p.x - q.x) < EPS)
            return p.y;
        return p.y + (q.y - p.y) * (x - p.x) / (q.x - p.x);
    }
};

bool intersect1d(ld l1, ld r1, ld l2, ld r2) {
    if (l1 > r1)
        swap(l1, r1);
    if (l2 > r2)
        swap(l2, r2);
    return max(l1, l2) <= min(r1, r2) + EPS;
}

int vec(const pt& a, const pt& b, const pt& c) {
    ld s = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    return abs(s) < EPS ? 0 : s > 0 ? +1 : -1;
}

bool intersect(const seg& a, const seg& b)
{
    return intersect1d(a.p.x, a.q.x, b.p.x, b.q.x) &&
           intersect1d(a.p.y, a.q.y, b.p.y, b.q.y) &&
           vec(a.p, a.q, b.p) * vec(a.p, a.q, b.q) <= 0 &&
           vec(b.p, b.q, a.p) * vec(b.p, b.q, a.q) <= 0;
}

bool operator<(const seg& a, const seg& b)
{
    ld x = max(min(a.p.x, a.q.x), min(b.p.x, b.q.x));
    return a.get_y(x) < b.get_y(x) - EPS;
}

struct event {
    ld x;
    int tp, id;

    event() {}
    event(ld _x, int _tp, int _id) : x(_x), tp(_tp), id(_id) {}

    bool operator<(const event& e) const {
        if (abs(x - e.x) > EPS)
            return x < e.x;
        return tp > e.tp;
    }
};

set<seg> s;
vector<set<seg>::iterator> where;

set<seg>::iterator prev(set<seg>::iterator it) {
    return it == s.begin() ? s.end() : --it;
}

set<seg>::iterator next(set<seg>::iterator it) {
    return ++it;
}

pair<int, int> solve(const vector<seg>& a) {
    int n = (int)a.size();
    vector<event> e;
    for (int i = 0; i < n; ++i) {
        e.push_back(event(min(a[i].p.x, a[i].q.x), +1, i));
        e.push_back(event(max(a[i].p.x, a[i].q.x), -1, i));
    }
    sort(e.begin(), e.end());

    s.clear();
    where.resize(a.size());
    for (size_t i = 0; i < e.size(); ++i) {
        int id = e[i].id;
        if (e[i].tp == +1) {
            set<seg>::iterator nxt = s.lower_bound(a[id]), prv = prev(nxt);
            if (nxt != s.end() && intersect(*nxt, a[id]))
                return MP(nxt->id, id);
            if (prv != s.end() && intersect(*prv, a[id]))
                return MP(prv->id, id);
            where[id] = s.insert(nxt, a[id]);
        } else {
            set<seg>::iterator nxt = next(where[id]), prv = prev(where[id]);
            if (nxt != s.end() && prv != s.end() && intersect(*nxt, *prv))
                return MP(prv->id, nxt->id);
            s.erase(where[id]);
        }
    }
    return MP(-1, -1);
}

vector<seg> bez(vector<seg> tab, int bez){
	vector<seg> ret;
	for(int i=0; i<sz(tab); i++)
		if(i!=bez)
			ret.pb(tab[i]);
	return ret;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int n;
	cin >> n;
	vector<seg> odcinki;	
	for(int i=0; i<n; i++){
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		odcinki.pb({{(ld)a, (ld)b}, {(ld)c, (ld)d}, i});
	}
	auto para = solve(odcinki);
	assert(para != MP(-1, -1));
	vector<int> ans;
	if(solve(bez(odcinki, para.f)) == MP(-1, -1))
		ans.pb(para.f+1);
	if(solve(bez(odcinki, para.s)) == MP(-1, -1))
		ans.pb(para.s+1);
	if(!sz(ans)){
		cout << "NIE\n";
		exit(0);
	}
	sort(all(ans));
	cout << ans[0] << '\n';
}
