#ifndef _VZL_SPHERE_H_
#define _VZL_SPHERE_H_

#include "ThingToHit.h"
#include "Vector.h"

namespace vzl
{

class Sphere : public ThingToHit
{
public:
    Sphere() = delete;
    Sphere(const Vector& center, double radius, const Color& color) 
        : ThingToHit(color), m_Center(center), m_Radius(radius) { }
    ~Sphere() { }
    double Intersection(const Ray& theRay) const override;
    Color Shade(const Vector& point, const Light& light) const override;
    inline const Vector Center() const { return m_Center; }
    inline double radius() const { return m_Radius; }
private:
    Vector m_Center;
    double m_Radius;
};


} // namespace vzl

#endif