#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include <cmath>
#include <vector>
#include <cassert>
#include <iostream>

template <size_t NUM, typename T>
struct vector {

private:
    T data_[NUM];

    vector() {
        for (size_t i = NUM; i--; data_[i] = T());
    }

    T& operator[](const size_t i) {
        assert(i < NUM);
        return data_[i];
    }

    const T& operator[](const size_t i) const {
        assert(i < NUM);
        return data_[i];
    }


};

typedef vector<2, float> Vec2f;
typedef vector<3, float> Vec3f;
typedef vector<3, int  > Vec3i;
typedef vector<4, float> Vec4f;

template <typename T>
struct vector<2,T> {

    T x,y;

    vector(): x(T()), y(T()) {}
    vector(T X, T Y): x(X), y(Y) {}

    template <class U> vector<2,T>(const vector<2,U> &v);

    T& operator[](const size_t i){
              assert(i < 2);
              return i <= 0 ? x : y;
          }

    const T& operator[](const size_t i) const {
              assert(i < 2);
              return i <= 0 ? x : y;
          }
};

template <typename T> struct vector<3,T> {

    T x,y,z;

    vector(): x(T()), y(T()), z(T()) {}
    vector(T X, T Y, T Z): x(X), y(Y), z(Z) {}

    T& operator[](const size_t i) {
        assert(i < 3);
        return i <= 0 ? x : (1 == i ? y : z);
    }

    const T& operator[](const size_t i) const {
        assert(i < 3);
        return i <= 0 ? x : (1 == i ? y : z);
    }

    float norm() {
        return std::sqrt(x*x + y*y + z*z);
    }

    vector<3,T> & normalize(T l = 1) {
        *this = (*this)*(l / norm());
        return *this;
    }
};

template <typename T> struct vector<4,T> {
    T x,y,z,w;

    vector() : x(T()), y(T()), z(T()), w(T()) {}
    vector(T X, T Y, T Z, T W) : x(X), y(Y), z(Z), w(W) {}

          T& operator[](const size_t i)       {
        assert(i<4);
        return i<=0 ? x : (1==i ? y : (2==i ? z : w));
    }

    const T& operator[](const size_t i) const {
        assert(i<4);
        return i<=0 ? x : (1==i ? y : (2==i ? z : w));
    }
};

template<size_t DIM,typename T>
T operator*(const vector<DIM,T>& lhs, const vector<DIM,T>& rhs) {
    T ret = T();
    for (size_t i=DIM; i--; ret+=lhs[i]*rhs[i]);
    return ret;
}

template<size_t DIM,typename T>vector<DIM,T>
operator+(vector<DIM,T> lhs, const vector<DIM,T>& rhs) {
    for (size_t i=DIM; i--; lhs[i]+=rhs[i]);
    return lhs;
}

template<size_t DIM,typename T>vector<DIM,T>
operator-(vector<DIM,T> lhs, const vector<DIM,T>& rhs) {
    for (size_t i=DIM; i--; lhs[i]-=rhs[i]);
    return lhs;
}

template<size_t DIM,typename T,typename U> vector<DIM,T>
operator*(const vector<DIM,T> &lhs, const U& rhs) {
    vector<DIM,T> ret;
    for (size_t i=DIM; i--; ret[i]=lhs[i]*rhs);
    return ret;
}

template<size_t DIM,typename T> vector<DIM,T>
operator-(const vector<DIM,T> &lhs) {
    return lhs*T(-1);
}

template <typename T> vector<3,T>
cross(vector<3,T> v1, vector<3,T> v2) {
    return vector<3,T>(v1.y*v2.z - v1.z*v2.y, v1.z*v2.x - v1.x*v2.z, v1.x*v2.y - v1.y*v2.x);
}

template <size_t DIM, typename T>
std::ostream& operator<<(std::ostream& out, const vector<DIM,T>& v) {
    for(unsigned int i=0; i<DIM; i++) out << v[i] << " ";
    return out;
}
#endif //__GEOMETRY_H__

