/**
 * @file Vector.h
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2019-06-19
 * 
 * @copyright Copyright (c) 2019
 * 
*/

#ifndef VECTOR_H
#define VECTOR_H
 
#include <iostream>
#include <cstdint>
#include <utility>

namespace monsterbattle
{
    template<typename T>
    struct Vector
    {
        Vector():
            x(0), y(0)
        {}


        Vector(const T& x, const T& y):
            x(x), y(y)
        {}

        Vector(const Vector& other):
            x(other.x), y(other.y)
        {}

        virtual ~Vector() = default;

        T x;
        T y;  

        Vector& operator*=(const Vector& other) { this->x *= other.x; this->y *= other.y;return *this; }
        Vector&  operator+=(const Vector& other) { this->x += other.x; this->y += other.y; return *this;}
        Vector&  operator-=(const Vector& other) { this->x -= other.x; this->y -= other.y; return *this;}
        Vector&  operator/=(const Vector& other) { this->x /= other.x; this->y /= other.y; return *this;}
        Vector&  operator=(const Vector& other) { this->x = other.x; this->y = other.y; return *this;}  

        Vector operator*(const Vector& other) { return std::move(Vector(this->x * other.x, this->y * other.y)); }
        Vector operator+(const Vector& other) { return std::move(Vector(this->x + other.x, this->y + other.y)); }
        Vector operator-(const Vector& other) { return std::move(Vector(this->x - other.x, this->y - other.y)); }
        Vector operator/(const Vector& other) { return std::move(Vector(this->x / other.x, this->y / other.y)); }

        template <typename U>
        friend std::ostream& operator<<(std::ostream& stream, const Vector<U>& vec)
        { 
            return stream << '{' << vec.x << ',' << vec.y << '}'; 
        }
    };

    using Vector2f = Vector<float>;
    using Vector2i = Vector<int>;
    using Vector2i8 = Vector<int8_t>;
    using Vector2i16 = Vector<int16_t>;
    using Vector2i32 = Vector<int32_t>;
    using Vector2i64 = Vector<int64_t>;

}

#endif
