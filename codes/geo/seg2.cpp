typedef long double K;

struct seg2{
	vec2 a, b;
	seg2(){}
	seg2(vec2 a, vec2 b) : a(a), b(b) {}
};
std::ostream & operator <<(std::ostream &out, seg2 s){ out << "(" << s.a.x << ", " << s.a.y << " -> " << s.b.x << ", " << s.b.y << ")"; return out; }

K dist(seg2 s, vec2 p) {
	vec2 d = s.b-s.a;
	p = p-s.a;
	return dist(std::max((K)0, std::min((K)1, dot(d, p)/dot(d, d)))*d, p);
}

bool _inter(K a, K b, K c, K d){
	if(a > b) std::swap(a, b);
	if(c > d) std::swap(c, d);
	return std::max(a, c) <= std::min(b, d);
}
bool intersect(seg2 a, seg2 b){
	if(side(b.a, a.a, b.b) == 0 && side(b.a, a.b, b.b) == 0)
		return _inter(a.a.x, a.b.x, b.a.x, b.b.x) && _inter(a.a.y, a.b.y, b.a.y, b.b.y);
	return side(a.a, a.b, b.a) != side(a.a, a.b, b.b) && side(b.a, b.b, a.a) != side(b.a, b.b, a.b);
}
