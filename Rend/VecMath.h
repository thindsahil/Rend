// This contains A LOT of duplication and no assertions
//	TODO: FIX LATER
#ifndef VECMATH_H
#define VECMATH_H

#include <iostream>
#include <cmath>

const float PI = 3.141592;

template<typename T>
struct Vec2 {
	union {
		struct { T x, y; };
		struct { T u, v; };
		T data[2];
	};
	Vec2() : x(0), y(0) {}
	Vec2(T a, T b) : x(a), y(b) {}
	bool operator ==(const Vec2<T>& other) const { return x == other.x && y == other.y; }
	Vec2<T> operator +(const Vec2<T>& right) const { return Vec2<T>(x + right.x, y + right.y); }
	Vec2<T> operator -(const Vec2<T>& right) const { return Vec2<T>(x - right.x, y - right.y); }
	Vec2<T> operator *(float f)          const { return Vec2<T>(x * f, y * f); }
	T& operator [](const int i) { return data[i]; }
	const T& operator [](const int i) const { return data[i]; }

	float length() const { return std::sqrt(x * x + y * y); }
	Vec2<T>& normalize(T l = 1) { *this = (*this) * (l / length()); return *this; }
};

template<typename T>
struct Vec3 {
	union {
		struct { T x, y, z; };
		//struct { T u, v, w; };
		T data[3];
	};
	Vec3() : x(0), y(0), z(0) {}
	Vec3(T a, T b, T c) : x(a), y(b), z(c) {}
	//Vec3(Vec4<T> V) : x(V.x), y(V.y), z(V.z) {}
	bool operator ==(const Vec3<T>& other) const { return x == other.x && y == other.y && z == other.z; }
	Vec3<T> operator +(const Vec3<T>& right) const { return Vec3<T>(x + right.x, y + right.y, z + right.z); }
	Vec3<T> operator -(const Vec3<T>& right) const { return Vec3<T>(x - right.x, y - right.y, z - right.z); }
	Vec3<T> operator *(float f)          const { return Vec3<T>(x * f, y * f, z * f); }
	T& operator [](const int i) { return data[i]; }
	const T& operator [](const int i) const { return data[i]; }

	float length() const { return std::sqrt(x * x + y * y + z * z); }
	Vec3<T>& normalize(T l = 1) { *this = (*this) * (l / length()); return *this; }
};

template<typename T>
struct Vec4 {
	union {
		struct { T x, y, z, w; };
		T data[4];
	};

	Vec4() : x(0), y(0), z(0), w(0) {}
	Vec4(T a, T b, T c, T d) : x(a), y(b), z(c), w(d) {}
	Vec4(Vec3<T> v, T d) : x(v.x), y(v.y), z(v.z), w(d) {}

	bool operator   ==(const Vec4<T>& other) const { return x == other.x && y == other.y && z == other.z && w == other.w; }
	Vec4<T> operator +(const Vec4<T>& right) const { return Vec4<T>(x + right.x, y + right.y, z + right.z, w + right.w); }
	Vec4<T> operator -(const Vec4<T>& right) const { return Vec4<T>(x - right.x, y - right.y, z - right.z, w - right.w); }
	Vec4<T> operator *(float f)              const { return Vec4<T>(x * f, y * f, z * f, w * f); }
	T& operator [](const int i) { return data[i]; }
	const T& operator [](const int i) const { return data[i]; }

	float length() const { return std::sqrt(x * x + y * y + z * z + w * w); }
	Vec4<T>& normalize(T l = 1) { *this = (*this) * (l / length()); return *this; }
};

// Dot Product 
template <typename T>
T dot(Vec2<T> v1, Vec2<T> v2) {
	T res = 0;
	res += (v1.x * v2.x);
	res += (v1.y * v2.y);
	return res;
}

template <typename T>
T dot(Vec3<T> v1, Vec3<T> v2) {
	T res = 0;
	res += (v1.x * v2.x);
	res += (v1.y * v2.y);
	res += (v1.z * v2.z);
	return res;
}

template <typename T>
T dot(Vec4<T> v1, Vec4<T> v2) {
	T res = 0;
	res += (v1.x * v2.x);
	res += (v1.y * v2.y);
	res += (v1.z * v2.z);
	res += (v1.w * v2.w);
	return res;
}


//	Cross Product 
template <typename T>
Vec3<T> cross(Vec3<T> v1, Vec3<T> v2) {
	return Vec3<T>(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
}



template <typename T> std::ostream& operator<<(std::ostream& s, Vec2<T>& v) {
	s << "(" << v.x << ", " << v.y << ")\n";
	return s;
}

template <typename T> std::ostream& operator<<(std::ostream& s, Vec3<T>& v) {
	s << "(" << v.x << ", " << v.y << ", " << v.z << ")\n";
	return s;
}

template <typename T> std::ostream& operator<<(std::ostream& s, Vec4<T>& v) {
	s << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")\n";
	return s;
}




template <typename T>
struct Mat3 {
	Vec3<T> data[3];

	Mat3() {
		data[0] = Vec3<T>();	// row vectors
		data[1] = Vec3<T>();
		data[2] = Vec3<T>();
	}
	Mat3(std::initializer_list<std::initializer_list<T>> init_list) {
		int i = 0, j = 0;
		for (std::initializer_list<T> row : init_list) {
			for (T num : row) {
				data[i][j] = num;
				j++;
			}
			i++;
			j = 0;
		}
	}
	Vec3<T>& operator[](const int i) { return data[i]; }	// returns ith row vector 
	const Vec3<T>& operator[](const int i) const { return data[i]; }

	Vec3<T> col(const int i) {	//	returns ith column vector
		Vec3<T> V;
		V.x = data[0][i];
		V.y = data[1][i];
		V.z = data[2][i];
		return V;
	}

	void setCol(const Vec3<T> V, const int i) {
		data[0][i] = V.x;
		data[1][i] = V.y;
		data[2][i] = V.z;
	}

	//	Matrix-Matrix multiplication
	Mat3<T> operator*(const Mat3<T>& O) const {
		Mat3<T> M;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				for (int k = 0; k < 3; k++) {
					M[i][j] += data[i][k] * O[k][j];
				}
			}
		}
		return M;
	}

	// Matrix-Vector multiplication
	Vec3<T> operator*(const Vec3<T>& V) const {
		Vec3<T> R;
		//for (int i = 0; i < 3; i++) {
		R.x = (data[0][0] * V.x + data[0][1] * V.y + data[0][2] * V.z);
		R.y = (data[1][0] * V.x + data[1][1] * V.y + data[1][2] * V.z);
		R.z = (data[2][0] * V.x + data[2][1] * V.y + data[2][2] * V.z);
		//}
		return R;
	}

};

template <typename T> std::ostream& operator<<(std::ostream& s, Mat3<T>& m) {
	s << "(" << m[0][0] << ", " << m[0][1] << ", " << m[0][2] << ")\n"
		<< "(" << m[1][0] << ", " << m[1][1] << ", " << m[1][2] << ")\n"
		<< "(" << m[2][0] << ", " << m[2][1] << ", " << m[2][2] << ")\n";
	return s;
}

template <typename T>
struct Mat4 {
	Vec4<T> data[4];

	Mat4() {
		data[0] = Vec4<T>();	// row vectors
		data[1] = Vec4<T>();
		data[2] = Vec4<T>();
		data[3] = Vec4<T>();
	}
	Mat4(std::initializer_list<std::initializer_list<T>> init_list) {
		int i = 0, j = 0;
		for (std::initializer_list<T> row : init_list) {
			for (T col : row) {
				data[i][j] = col;
				j++;
			}
			i++;
			j = 0;
		}
	}
	Vec4<T>& operator[](const int i) { return data[i]; }	//	returns ith row vector
	const Vec4<T>& operator[](const int i) const { return data[i]; }

	Vec4<T> col(const int i) {	//	returns ith column vector
		Vec4<T> V;
		V.x = data[0][i];
		V.y = data[1][i];
		V.z = data[2][i];
		V.w = data[3][i];
		return V;
	}

	void setCol(const Vec4<T> V, const int i) {
		data[0][i] = V.x;
		data[1][i] = V.y;
		data[2][i] = V.z;
		data[3][i] = V.w;
	}

	//	Matrix-Matrix multiplication
	Mat4<T> operator*(const Mat4<T>& O) const {
		Mat4<T> M;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				for (int k = 0; k < 4; k++) {
					M[i][j] += data[i][k] * O[k][j];
				}
			}
		}
		return M;
	}

	// Matrix-Vector multiplication
	Vec4<T> operator*(const Vec4<T>& V) const {
		Vec4<T> R;
		//for (int i = 0; i < 3; i++) {
		R.x = (data[0][0] * V.x + data[0][1] * V.y + data[0][2] * V.z + data[0][3] * V.w);
		R.y = (data[1][0] * V.x + data[1][1] * V.y + data[1][2] * V.z + data[1][3] * V.w);
		R.z = (data[2][0] * V.x + data[2][1] * V.y + data[2][2] * V.z + data[2][3] * V.w);
		R.w = (data[3][0] * V.x + data[3][1] * V.y + data[3][2] * V.z + data[3][3] * V.w);
		//}
		return R;
	}
};

template <typename T> std::ostream& operator<<(std::ostream& s, Mat4<T>& m) {
	s << "(" << m[0][0] << ", " << m[0][1] << ", " << m[0][2] << ", " << m[0][3] << ")\n"
		<< "(" << m[1][0] << ", " << m[1][1] << ", " << m[1][2] << ", " << m[1][3] << ")\n"
		<< "(" << m[2][0] << ", " << m[2][1] << ", " << m[2][2] << ", " << m[2][3] << ")\n"
		<< "(" << m[3][0] << ", " << m[3][1] << ", " << m[3][2] << ", " << m[3][3] << ")\n";
	return s;
}

typedef Vec2<int> Vec2I;
typedef Vec2<float> Vec2F;
typedef Vec3<int> Vec3I;
typedef Vec3<float> Vec3F;
typedef Vec4<int> Vec4I;
typedef Vec4<float> Vec4F;

typedef Mat3<int> Mat3I;
typedef Mat3<float> Mat3F;
typedef Mat4<float> Mat4F;




//	move elsewhere later
struct Vertex {
	Vec3F pos;
	Vec2F UV;
	Vec3F normal;
};


#endif