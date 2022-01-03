#ifndef _VZL_TRIANGLE_H_
#define _VZL_TRIANGLE_H_

#include "ThingToHit.h"
#include "Vector.h"
#include "Color.h"
#include <vector>

namespace vzl
{


class Triangle : public ThingToHit
{
public:
    Triangle() = delete;
    ~Triangle() {}
    Triangle(const Vector& p0, const Vector& p1, const Vector& p2, const Color& color);

    inline const std::vector<Vector>& GetPoints() const { return m_Points; }
    inline const std::vector<Vector>& GetEdges() const { return m_Edges; }
    inline const Vector& GetNormal() const { return m_Normal; }
    inline const double GetArea() const { return m_Area; }
    inline const double GetAspectRatio() const { return m_AspectRatio; }

    IntersectionData Intersection(const Ray& theRay) const override;
    Color Shade(const Vector& point, const Light& light) const override;
	const AABB aabb() const override;
	void PrintInfo() const;
private:
    std::vector<Vector> m_Points, m_Edges;
    Vector m_Normal;
    double m_Area, m_AspectRatio;
	AABB m_AABB; 
    /*private functions*/
    void CalculateProperties();
	void CalculateAABB();
};


}
#endif
