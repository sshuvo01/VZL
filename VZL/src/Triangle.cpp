#include "Triangle.h"
#include <cstdlib>
#include <iostream>
#include <algorithm>

namespace vzl
{


Triangle::Triangle(const Vector& p0, const Vector& p1, const Vector& p2, const Color& color)
    : ThingToHit(color), m_Points{ p0, p1, p2 }
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

} // namespace vzl