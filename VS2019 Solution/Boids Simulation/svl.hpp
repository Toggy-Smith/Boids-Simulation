#include <cmath>

namespace svl
{
    template <class BaseType>
    class Vector2 {
    public:
        BaseType x;
        BaseType y;

    public:
        Vector2
        (BaseType x, BaseType y)
            : x(x), y(y)
        {}

        Vector2()
            : x(0), y (0)
        {}

        Vector2
        (const Vector2& copy)
            : x(copy.x), y(copy.y)
        {}

        Vector2& operator=
        (const Vector2& vector)
        {
            x = vector.x;
            y = vector.y;

            return *this;
        }

        template <typename Scalar>
        Vector2 operator*
        (Scalar scalar)
        {
            return Vector2{ x * scalar,
                           y * scalar };
        }

        template <typename Scalar>
        void operator*=
        (Scalar scalar)
        {
            x *= scalar;
            y *= scalar;
        }

        template <typename Scalar>
        Vector2 operator/
        (Scalar scalar)
        {
            return Vector2{ x / scalar,
                           y / scalar };
        }

        template <typename Scalar>
        void operator/=
        (Scalar scalar)
        {
            x /= scalar;
            y /= scalar;
        }

        Vector2 operator+
        (const Vector2& vector) const
        {
            return Vector2{ x + vector.x,
                           y + vector.y };
        }

        void operator+=
        (const Vector2& vector)
        {
            x += vector.x;
            y += vector.y;
        }

        Vector2 operator-
        (const Vector2& vector) const
        {
            return Vector2{ x - vector.x,
                           y - vector.y };
        }

        void operator-=
        (const Vector2& vector)
        {
            x -= vector.x;
            y -= vector.y;
        }

        float getMagnitude() {
            return std::sqrt(
                std::pow(x, 2)
                +
                std::pow(y, 2)
            );
        }

        void setMagnitude(float magnitude) {
            normalize();

            (*this) *= magnitude;
        }

        Vector2 normalize() {
            float mag = getMagnitude();

            if (mag == 0)
                return *this;

            x /= mag;
            y /= mag;

            return Vector2{ x, y };
        }

        float dotProduct
        (Vector2& vector) {
            return (x * vector.x) +
                (y * vector.y);
        }
    };

    typedef Vector2<double>       Vector2d;
    typedef Vector2<float>        Vector2f;
    typedef Vector2<int>          Vector2i;
    typedef Vector2<unsigned int> Vector2u;
}