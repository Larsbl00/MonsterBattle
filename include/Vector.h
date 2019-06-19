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

namespace monsterbattle
{
    template<typename T>
    struct Vector
    {
        Vector(const T& x, const T& y):
            x(x), y(y)
        {}

        Vector(const Vector& other) = default;
        virtual ~Vector();

        T x,y;  

        Vector&& operator=(const Vector& other) = default;
        void operator*=(const Vector& other){this->x *= other.x; this->y *= other.y;}
        void operator+=(const Vector& other){this->x += other.x; this->y += other.y;}
        void operator-=(const Vector& other){this->x -= other.x; this->y -= other.y;}
        void operator/=(const Vector& other){this->x /= other.x; this->y /= other.y;}
        
        Vector&& operator*(const Vector& other) {return Vector(this->x * other.x, this->y * other.y);}
        Vector&& operator+(const Vector& other) {return Vector(this->x + other.x, this->y + other.y);}
        Vector&& operator-(const Vector& other) {return Vector(this->x - other.x, this->y - other.y);}
        Vector&& operator/(const Vector& other) {return Vector(this->x / other.x, this->y / other.y);}

        friend std::ostream& operator<<(std::ostream& stream, const Vector<T> vec)
        {
            return std::cout << '{' << vec.x << ',' << vec.y << '}';
        }
    };

    using Vector2f = Vector<float>;
    using Vector2i = Vector<int>;
    using Vector2i8 = Vector<uint8_t>;
    using Vector2i16 = Vector<uint16_t>;
    using Vector2i32 = Vector<uint32_t>;
    using Vector2i64 = Vector<uint64_t>;

}

#endif