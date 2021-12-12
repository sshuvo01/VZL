#include "Scene.h"

namespace vzl
{

void Scene::AddObject(ThingToHit* object)
{
    m_SceneObjects.push_back(object);
}

void Scene::AddLight(Light* light)
{
    m_SceneLights.push_back(light);
}

ThingToHit* Scene::GetObject(size_t index) const
{
    if(index < 0 || index >= m_SceneObjects.size())
    {
        return nullptr;
    }
    return m_SceneObjects[index];
}

Light* Scene::GetLight(size_t index) const
{
    if(index < 0 || index >= m_SceneLights.size())
    {
        return nullptr;
    }
    return m_SceneLights[index];
}


}