typedef long double ld;

struct vec2{
	ld x, y;
	vec2(){}
	vec2(ld a, ld b) : x(a), y(b) {}
	vec2 operator -(){ return vec2(-this->x, -this->y); }
};
vec2 operator +(vec2 a, vec2 b){ return vec2(a.x+b.x, a.y+b.y); }
vec2 operator -(vec2 a, vec2 b){ return vec2(a.x-b.x, a.y-b.y); }
vec2 operator *(ld k, vec2 a){ return vec2(k*a.x, k*a.y); }
ld dot(vec2 a, vec2 b){ return a.x*b.x + a.y*b.y; }
ld det(vec2 a, vec2 b){ return a.x*b.y-a.y*b.x; }
ld length2(vec2 a){ return dot(a, a); }
ld length(vec2 a){ return std::sqrt(dot(a, a)); }
vec2 normal(vec2 a){ return (1/length(a))*a; }
ld dist2(vec2 a, vec2 b){ return length2(a-b); }
ld dist(vec2 a, vec2 b){ return length(a-b); }
vec2 proj(vec2 a, vec2 b){ return (dot(a, b)/dot(b, b))*b; }
