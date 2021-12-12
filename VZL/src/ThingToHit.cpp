#include "ThingToHit.h"
#include <algorithm>

namespace vzl
{


bool ThingToHit::IsIgnoredLight(Light* light) const
{
    auto iter = std::find(m_IgnoredLight.begin(), m_IgnoredLight.end(), light);
    return iter != m_IgnoredLight.end();
}


} // namespace vzl