#ifndef _VZL_PLANE_H_
#define _VZL_PLANE_H_
#include "ThingToHit.h"
#include "Vector.h"
#include "Color.h"

namespace vzl
{


class Plane : public ThingToHit
{
public:
    Plane() = delete;//: m_Color{1.0, 0.0, 0.0, 1.0}, m_Normal(0.0, 1.0, 0.0), m_PointOnPlane{} { }
    Plane(const Vector& normal, const Vector& point, const Color& color) 
        : ThingToHit(color), m_Normal(normal), m_PointOnPlane(point) { m_Normal.normalize(); }
    ~Plane() { }

    IntersectionData Intersection(const Ray& theRay) const override;
    Color Shade(const Vector& point, const Light& light) const override;
private:
    Vector m_Normal;
    Vector m_PointOnPlane;
};


} // namespace vzl

#endif