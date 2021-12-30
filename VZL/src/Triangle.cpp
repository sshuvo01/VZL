#include "Triangle.h"
#include <cstdlib>
#include <iostream>
#include <algorithm>

namespace vzl
{


Triangle::Triangle(const Vector& p0, const Vector& p1, const Vector& p2, const Color& color)
    : ThingToHit(color), m_Points{ p0, p1, p2 }, m_AABB{{}, {}}
{
    CalculateProperties();
}

void Triangle::CalculateProperties()
{
    m_Edges.push_back(m_Points[1] - m_Points[0]); // e1
    m_Edges.push_back(m_Points[2] - m_Points[0]); // e2
    m_Edges.push_back(m_Points[2] - m_Points[1]); // e3

    m_Normal = m_Edges[1] ^ m_Edges[0];
    m_Normal.normalize();

    m_Area = 0.5 * (m_Edges[1] ^ m_Edges[0]).magnitude();

    double maxEdge = std::max( std::max( m_Edges[0].magnitude(), m_Edges[1].magnitude() ), m_Edges[2].magnitude() );
    double minEdge = std::min( std::min( m_Edges[0].magnitude(), m_Edges[1].magnitude() ), m_Edges[2].magnitude() );
    m_AspectRatio = maxEdge / minEdge;

	CalculateAABB();
}

void Triangle::CalculateAABB()
{
	Vector llc = m_Points[0];
	Vector urc = llc;

	for (size_t i = 1; i < 3; i++)
	{
		llc[0] = std::min(llc[0], m_Points[i][0]); // x
		llc[1] = std::min(llc[1], m_Points[i][1]); // y
		llc[2] = std::min(llc[2], m_Points[i][2]); // z

		urc[0] = std::max(urc[0], m_Points[i][0]);
		urc[1] = std::max(urc[1], m_Points[i][1]);
		urc[2] = std::max(urc[2], m_Points[i][2]);
	}

	m_AABB = { llc, urc };
}


double Triangle::Intersection(const Ray& theRay) const
{
    Vector e1 = m_Edges[0];
    Vector e2 = m_Edges[1];
    Vector d = theRay.GetDirection();
    Vector R0 = theRay.GetPosition();
    Vector P0 = m_Points[0];

    double denom = d * m_Normal;

    if(denom == 0.0)
    {
        return -1.0;
    }

    double numer = -(R0 - P0) * m_Normal;
    double t = numer / denom;

    if(t < 0.0)
    {
        return -1.0;
    }
    
    Vector p = theRay.GetPosition() + t * theRay.GetDirection();
    Vector pp0 = p - m_Points[0];
    Vector e2e1 = e2 ^ e1;
    double e2e1Mag = e2e1.magnitude();
    double u = ((e2 ^ pp0) * e2e1) / (e2e1Mag * e2e1Mag);

    Vector e1e2 = e1 ^ e2;
    double e1e2Mag = e1e2.magnitude();
    double v = ((e1 ^ pp0) * e1e2) / (e2e1Mag * e2e1Mag);

    if(u < 0.0 || u > 1.0)
    {
        return -1.0;
    }
    if(v < 0.0 || v > 1.0)
    {
        return -1.0;
    }
    double uv = u + v;
    if(uv < 0.0 || uv > 1.0)
    {
        return -1.0;
    }

    return t;
}

Color Triangle::Shade(const Vector& point, const Light& light) const
{
    Vector lightDir = (light.GetPosition() - point).unitvector();
    //float reflectivity = std::max(m_Normal * lightDir, 0.0);
    float reflectivity = std::abs(m_Normal * lightDir);
    return GetColor() * light.GetColor() * reflectivity;
}

const AABB Triangle::aabb() const
{
	return m_AABB;
}

void Triangle::PrintInfo() const
{
	for (size_t i = 0; i < m_Points.size(); i++)
	{
		std::cout << "Vertex " << i << ": " << m_Points[i].X() << ", " << m_Points[i].Y() << ", " << m_Points[i].Z() << std::endl;
	}
	std::cout << "Color: " << m_Color.red() << ", " << m_Color.green() << ", " << m_Color.blue() << ", " << m_Color.alpha() << std::endl;
}

} // namespace vzl