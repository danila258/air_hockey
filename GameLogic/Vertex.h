#ifndef Vertex_H
#define Vertex_H

#include <utility>


template<typename T>
struct Vertex
{
    T _x;
    T _y;

    Vertex() = default;
    Vertex(T x, T y);

    ~Vertex() = default;

    Vertex(const Vertex& other);
    Vertex(Vertex&& other) noexcept;

    Vertex& operator=(const Vertex& other);
    Vertex& operator=(Vertex&& other) noexcept;

    Vertex operator+(const Vertex& other);
    Vertex& operator+=(const Vertex& other);

    Vertex operator-(const Vertex& other);
    Vertex& operator-=(const Vertex& other);
};


template<typename T>
Vertex<T>::Vertex(T x, T y) : _x(x), _y(y)
{}

template<typename T>
Vertex<T>::Vertex(const Vertex& other) : Vertex(other._x, other._y)
{}

template<typename T>
Vertex<T>::Vertex(Vertex&& other) noexcept
{
    *this = std::move(other);
}

template<typename T>
Vertex<T>& Vertex<T>::operator=(const Vertex& other)
{
    if (this == &other)
    {
        return *this;
    }

    Vertex<T> vertexCopy(other);
    *this = std::move(vertexCopy);

    return *this;
}

template<typename T>
Vertex<T>& Vertex<T>::operator=(Vertex&& other) noexcept
{
    std::swap(_x, other._x);
    std::swap(_y, other._y);

    return *this;
}

template<typename T>
Vertex<T> Vertex<T>::operator+(const Vertex& other)
{
    Vertex copy(*this);
    return copy += other;
}

template<typename T>
Vertex<T>& Vertex<T>::operator+=(const Vertex& other)
{
    *this = *this + other;
    return *this;
}

template<typename T>
Vertex<T> Vertex<T>::operator-(const Vertex& other)
{
    Vertex copy(*this);
    return copy -= other;
}

template<typename T>
Vertex<T>& Vertex<T>::operator-=(const Vertex& other)
{
    *this = *this - other;
    return *this;
}


#endif // Vertex_H
