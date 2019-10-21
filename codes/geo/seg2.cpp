typedef long double K;

struct seg2{
	vec2 a, b;
	seg2(){}
	seg2(vec2 a, vec2 b) : a(a), b(b) {}
};

K dist(seg2 s, vec2 p) {
	vec2 d = s.b-s.a;
	p = p-s.a;
	return dist(std::max((K)0, std::min((K)1, dot(d, p)/dot(d, d)))*d, p);
}
std::ostream & operator <<(std::ostream &out, seg2 s){ out << "(" << s.a.x << ", " << s.a.y << " -> " << s.b.x << ", " << s.b.y << ")"; return out; }
