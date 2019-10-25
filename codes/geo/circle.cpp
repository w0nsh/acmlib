typedef long double K;

struct circle{
	vec2 p; K r;
	circle(){}
	circle(vec2 p, K r) : p(p), r(r) {}
};
std::ostream & operator <<(std::ostream &out, circle c){ out << "((" << c.p.x << ", " << c.p.y << "), " << c.r << ")"; return out; }

// przeciecie okregu z prosta/okregiem
K EPS = 1e-10;
vec2 EMPTY = vec2(1e20, 1e20);
std::pair<vec2, vec2> intersection(circle c, line2 l){
	l = translate(l, -1*c.p);
	K x0 = l.n.x*l.c/len2(l.n), y0 = l.n.y*l.c/len2(l.n);
	if(l.c*l.c > c.r*c.r*len2(l.n)+EPS) return std::pair<vec2, vec2>(EMPTY, EMPTY);
	else if(std::abs(l.c*l.c - c.r*c.r*len2(l.n)) < EPS) return std::pair<vec2, vec2>(c.p+vec2(x0, y0), EMPTY);
	double m = std::sqrt((c.r*c.r-l.c*l.c/len2(l.n))/len2(l.n));
	return std::pair<vec2, vec2>(c.p+vec2(x0+l.n.y*m, y0-l.n.x*m), c.p+vec2(x0-l.n.y*m, y0+l.n.x*m));
}
std::pair<vec2, vec2> intersection(circle a, circle b){
	assert(dist2(a.p, b.p) > EPS);
	vec2 t = a.p;
	a.p = a.p-t; b.p = b.p-t;
	std::pair<vec2, vec2> ret = intersection(a, line2(-2*b.p.x, -2*b.p.y, len2(b.p)+a.r*a.r-b.r*b.r));
	ret.first = (ret.first == EMPTY ? EMPTY : t+ret.first);
	ret.second = (ret.second == EMPTY ? EMPTY : t+ret.second);
	return ret;
}
