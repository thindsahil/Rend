
template<typename T> 
struct Vec2 {
	union {
		struct { T x, y; };
		struct { T u, v; };
		T data[2];
	};
	Vec2() : x(0), y(0) {}
	Vec2(T a, T b) : x(a), y(b) {}
};

typedef Vec2<int> Vec2I;
typedef Vec2<float> Vec2F;