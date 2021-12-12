#ifndef _VZL_RAY_H__
#define _VZL_RAY_H__
#include "Vector.h"

namespace vzl
{

class Ray
{
public:
    Ray() = default;
    Ray(const Vector& position, const Vector& direction);
    
    const Vector& GetPosition() const;
    const Vector& GetDirection() const;
    const Vector GetPointOnRay(double t) const;
    inline void SetPosition(const Vector& position) { m_Position = position; }
    inline void SetDirection(const Vector& direction) { m_Direction = direction; }
private:
    Vector m_Position, m_Direction;
};

}

#endif