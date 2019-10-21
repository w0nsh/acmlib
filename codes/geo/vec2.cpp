typedef long double K;

struct vec2{
	K x, y;
	vec2(){}
	vec2(K x, K y) : x(x), y(y) {}
	vec2 operator -(){ return vec2(-this->x, -this->y); }
};
vec2 operator +(vec2 a, vec2 b){ return vec2(a.x+b.x, a.y+b.y); }
vec2 operator -(vec2 a, vec2 b){ return vec2(a.x-b.x, a.y-b.y); }
vec2 operator *(K k, vec2 a){ return vec2(k*a.x, k*a.y); }
K dot(vec2 a, vec2 b){ return a.x*b.x + a.y*b.y; }
K det(vec2 a, vec2 b){ return a.x*b.y-a.y*b.x; }
K len2(vec2 a){ return dot(a, a); }
K len(vec2 a){ return std::sqrt(dot(a, a)); }
vec2 norm(vec2 a){ return (1/len(a))*a; }
vec2 perp(vec2 a) { return vec2(-a.y, a.x); }
K dist2(vec2 a, vec2 b){ return len2(a-b); }
K dist(vec2 a, vec2 b){ return len(a-b); }
vec2 proj(vec2 w, vec2 v){ return (dot(v, w)/dot(w, w))*w; }
K angle(vec2 a, vec2 b){ return std::acos(std::max((K)-1, std::min((K)1, dot(a, b)*(1/(len(a)*len(b)))))); }
std::ostream & operator <<(std::ostream &out, vec2 a){ out << "(" << a.x << ", " << a.y << ")"; return out; }
