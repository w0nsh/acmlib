typedef long double ld;

struct vec3{
	ld x, y, z;
	vec3(){}
	vec3(ld a, ld b, ld c) : x(a), y(b), z(c) {}
	vec3 operator -(){ return vec3(-this->x, -this->y, -this->z); }
};
vec3 operator +(vec3 a, vec3 b){ return vec3(a.x+b.x, a.y+b.y, a.z+b.z); }
vec3 operator -(vec3 a, vec3 b){ return vec3(a.x-b.x, a.y-b.y, a.z-b.z); }
vec3 operator *(ld k, vec3 a){ return vec3(k*a.x, k*a.y, k*a.z); }
ld dot(vec3 a, vec3 b){ return a.x*b.x + a.y*b.y + a.z*b.z; }
vec3 cross(vec3 a, vec3 b){ return vec3(a.y*b.z-a.z*b.y, a.z*b.x-a.x*b.z, a.x*b.y-a.y*b.x); }
ld length2(vec3 a){ return dot(a, a); }
ld length(vec3 a){ return std::sqrt(dot(a, a)); }
vec3 normal(vec3 a){ return (1/length(a))*a; }
ld dist2(vec3 a, vec3 b){ return length2(a-b); }
ld dist(vec3 a, vec3 b){ return length(a-b); }
vec3 proj(vec3 a, vec3 b){ return (dot(a, b)/dot(b, b))*b; }
