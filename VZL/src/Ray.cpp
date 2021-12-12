#include "Ray.h"
#include <iostream>

namespace vzl
{

Ray::Ray(const Vector& position, const Vector& direction)
: m_Position(position), m_Direction(direction)
{
    //std::cout << "Ray created\n";
}

const Vector Ray::GetPointOnRay(double t) const
{
    return m_Position + m_Direction * t;
}

const Vector& Ray::GetPosition() const
{
    return m_Position;
}

const Vector& Ray::GetDirection() const
{
    return m_Direction;
}

} // namespace vzl

