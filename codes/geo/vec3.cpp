typedef long double K;

struct vec3{
	K x, y, z;
	vec3(){}
	vec3(K x, K y, K z) : x(x), y(y), z(z) {}
	vec3 operator -(){ return vec3(-this->x, -this->y, -this->z); }
};
vec3 operator +(vec3 a, vec3 b){ return vec3(a.x+b.x, a.y+b.y, a.z+b.z); }
vec3 operator -(vec3 a, vec3 b){ return vec3(a.x-b.x, a.y-b.y, a.z-b.z); }
vec3 operator *(K k, vec3 a){ return vec3(k*a.x, k*a.y, k*a.z); }
K dot(vec3 a, vec3 b){ return a.x*b.x + a.y*b.y + a.z*b.z; }
vec3 cross(vec3 a, vec3 b){ return vec3(a.y*b.z-a.z*b.y, a.z*b.x-a.x*b.z, a.x*b.y-a.y*b.x); }
K len2(vec3 a){ return dot(a, a); }
K len(vec3 a){ return std::sqrt(dot(a, a)); }
vec3 norm(vec3 a){ return (1/len(a))*a; }
K dist2(vec3 a, vec3 b){ return len2(a-b); }
K dist(vec3 a, vec3 b){ return len(a-b); }
vec3 proj(vec3 w, vec3 v){ return (dot(v, w)/dot(w, w))*w; }
K angle(vec3 a, vec3 b){ return std::acos(std::max((K)-1, std::min((K)1, dot(a, b)*(1/(len(a)*len(b)))))); }
std::ostream & operator <<(std::ostream &out, vec3 a){ out << "(" << a.x << ", " << a.y << ", " << a.z << ")"; return out; }
