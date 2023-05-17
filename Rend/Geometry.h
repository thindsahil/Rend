
template<typename T> 
struct Vec2 {
	union {
		struct { T x, y; };
		struct { T u, v; };
		T data[2];
	};
	Vec2() : x(0), y(0) {}
	Vec2(T a, T b) : x(a), y(b) {}
	inline Vec2<T> operator +(const Vec2<T>& V) const { return Vec2<T>(x + V.x, y + V.y); }
	inline Vec2<T> operator -(const Vec2<T>& V) const { return Vec2<T>(x - V.x, y - V.y); }
};

template<typename T>
struct Vec3 {
	union {
		struct { T x, y, z; };
		struct { T u, v, w; };
		T data[3];
	};
	Vec3() : x(0), y(0), z(0) {}
	Vec3(T a, T b, T c) : x(a), y(b), z(c) {}
};

typedef Vec2<int> Vec2I;
typedef Vec2<float> Vec2F;
typedef Vec3<int> Vec3I;
typedef Vec3<float> Vec3F;