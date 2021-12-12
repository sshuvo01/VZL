#ifndef _VZL_THINGTOHIT_H_
#define _VZL_THINGTOHIT_H_

#include "Ray.h"
#include "Color.h"
#include "Vector.h"
#include "Light.h"
#include <vector>

namespace vzl
{


	class ThingToHit
	{
	public:
		ThingToHit() = delete;
		ThingToHit(const Color& color) : m_Color(color) { }
		virtual ~ThingToHit() { }

		virtual double Intersection(const Ray& theRay) const = 0;
		virtual Color Shade(const Vector& point, const Light& light) const = 0;
		inline Color GetColor() const { return m_Color; }
		inline void SetColor(const Color& color) { m_Color = color; }

		inline void AddIgnoredLight(Light* light) { m_IgnoredLight.push_back(light); }
		bool IsIgnoredLight(Light* light) const;

	protected:
		Color m_Color;
		std::vector<Light*> m_IgnoredLight;
	};

} // namespace vzl

#endif