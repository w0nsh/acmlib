typedef long double K;

struct line2{
	vec2 n; K c; // prosta n*v = c (n - wektor nomalny, v - punkty na prostej)
	line2(){}
	line2(vec2 n, K c) : n(n), c(c) {}
	line2(K a, K b, K c) : n(vec2(a, b)), c(-c) {} // ax+by+c=0
	line2(vec2 s, vec2 e) : n(vec2(s.y-e.y, e.x-s.x)), c(det(e,s)) {} // przechodzi przez punkty s, e
};
std::ostream & operator <<(std::ostream &out, line2 l){ out << "(" << l.n.x << "x + " << l.n.y << "y + " << -l.c << " = 0)"; return out; }

vec2 proj(line2 l, vec2 p){ return proj(perp(l.n), p)+(l.c/len2(l.n))*norm(l.n); }
K dist(line2 l, vec2 p) { return std::abs(dot(l.n, p)-l.c)/len(l.n); }
line2 translate(line2 l, vec2 d){ return line2(l.n, l.c+dot(l.n, d)); }
line2 parallel(line2 l, vec2 p){ return line2(l.n, dot(l.n, p)); } // prosta przechodzi przez p
line2 perp(line2 l, vec2 p){ return line2(perp(l.n), det(l.n, p)); } // prosta przechodzi przez p
