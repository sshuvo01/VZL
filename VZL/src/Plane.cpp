
#include "Plane.h"
#include <algorithm>

namespace vzl
{

IntersectionData Plane::Intersection(const Ray& theRay) const
{
    double denom = theRay.GetDirection() * m_Normal;
    if (denom == 0.0)
    {
		return { -1.0, nullptr };
    }
    double numer = -(theRay.GetPosition() - m_PointOnPlane) * m_Normal;
    double t = numer / denom;
    if(t < 0.0)
    {
		return { -1.0, nullptr };
    }
    
	return { t, this };
}

Color Plane::Shade(const Vector& point, const Light& light) const
{
    Vector lightDir = (light.GetPosition() - point).unitvector();
    float reflectivity = std::max(m_Normal * lightDir, 0.0);
    return GetColor() * light.GetColor() * reflectivity;
}

}// namespace vzl