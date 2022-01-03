#include "Sphere.h"
#include <cstdlib>
#include <algorithm>
#include <iostream>

namespace vzl
{



IntersectionData Sphere::Intersection(const Ray& theRay) const
{
    Vector RmC = theRay.GetPosition() - m_Center;
    double temp = theRay.GetDirection() * RmC;
    double f = temp * temp + m_Radius * m_Radius - RmC.magnitude() * RmC.magnitude();

    if(f < 0.0)
    {
		return { -1.0, nullptr };
    }

    const double EPSILON = 0.0000001;
    if(f > -EPSILON && f < EPSILON)
    {
        #ifdef DEBUG_SPHERE
            double t = -temp;
            if(t >= 0.0)
            {
                Vector p = theRay.GetPointOnRay(t);
                std::cout << "f == 0.0, Hit the sphere at " << p[0] << ", " << p[1] << ", " << p[2] << std::endl;
                std::cout << "Distance from centert: " << (m_Center - p).magnitude() << std::endl;
                double dist = (m_Center - p).magnitude();
                std::cout << "Distance from center: " << dist << std::endl;
                if(dist > 1.01)
                {
                    std::cout << "something is wrong\n";
                    std::cout << "dist: " << dist << std::endl;
                    std::cin.get();
                }
                return t;
            }
            return -1.0;
        #endif
			return { -temp, this };
    }


    if(f > 0.0)
    {
        #ifdef DEBUG_SPHERE
            double t1 = -temp + std::sqrt(f);
            double t2 = -temp - std::sqrt(f);
            double t = std::min(t1, t2);
            if(t >= 0.0)
            {
                Vector p = theRay.GetPointOnRay(t);
                std::cout << "f > 0.0, Hit the sphere at " << p[0] << ", " << p[1] << ", " << p[2] << std::endl;
                double dist = (m_Center - p).magnitude();
                std::cout << "Distance from center: " << dist << std::endl;
                if(dist > 1.01)
                {
                    std::cout << "something is wrong\n";
                    std::cout << "dist: " << dist << std::endl;
                    std::cin.get();
                }

                return t;
            }
            else return -1.0;
        #endif
    }
	return { std::min(-temp + std::sqrt(f), -temp - std::sqrt(f)), this };
}

Color Sphere::Shade(const Vector& point, const Light& light) const
{
    Vector normal = (point - m_Center).unitvector();
    Vector lightDir = (light.GetPosition() - point).unitvector();
    double reflectivity = std::max(normal * lightDir, 0.0);
    //std::cout << "Bla bla!" << std::endl;
    return light.GetColor() * GetColor() * reflectivity;
}

} // namespace vzl