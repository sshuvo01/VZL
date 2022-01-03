#ifndef _VZL_SCENE_H_
#define _VZL_SCENE_H_
#include <vector>
#include <limits>
#include <algorithm>
#include <iostream>
#include "ThingToHit.h"
#include "Light.h"
#include "Ray.h"
#include "Sphere.h"

namespace vzl
{


class Scene
{
public:
    Scene() = default;
    void AddObject(ThingToHit* object);
    void AddLight(Light* light);
    inline size_t GetNbObjects() const { return m_SceneObjects.size(); }
    inline size_t GetNbLights() const { return m_SceneLights.size(); }

    ThingToHit* GetObject(size_t index) const;
    Light* GetLight(size_t index) const;

    //ThingToHit* operator[](size_t index);
    std::vector<ThingToHit*> m_SceneObjects;
    std::vector<Light*> m_SceneLights;
};

inline Color Trace(const Ray& theRay, const Scene& theScene, const Color& bgColor = { 0.2, 0.2, 0.2, 1.0 })
{
    //std::cout << "number of objects: " << theScene.GetNbObjects()  << std::endl;
    double t = std::numeric_limits<double>::max();
    ThingToHit* nearestObjectHit = nullptr;
	IntersectionData iData;

    for(size_t i = 0; i < theScene.GetNbObjects(); i++)
    {
        ThingToHit* anObject = theScene.GetObject(i);
        
        if(anObject)
        {
            //std::cout << "aaaa\n";
            IntersectionData id =  anObject->Intersection(theRay);
            double tHit =  id.t;
            if(tHit > 0.0)
            {
                if(tHit < t)
                {
                    t = tHit;
					iData = id;
                    nearestObjectHit = anObject;
                }
            }
        }
    }

    if(!nearestObjectHit)
    {
        // nothing was hit
        return bgColor;
    }

    // compute the color!!!
    Color finalColor{};
    for(size_t i = 0; i < theScene.GetNbLights(); i++)
    {
        Vector hitPoint = theRay.GetPointOnRay(t);
        Light* light = theScene.GetLight(i);
        if(!light) continue;

        if(nearestObjectHit->IsIgnoredLight(light)) continue;

        //finalColor += nearestObjectHit->Shade(hitPoint, *light);
		finalColor += iData.geom->Shade(hitPoint, *light);
    }

    return finalColor;
} // end of Trace

}

#endif 