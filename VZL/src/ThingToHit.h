#ifndef _VZL_THINGTOHIT_H_
#define _VZL_THINGTOHIT_H_

#include "Ray.h"
#include "Color.h"
#include "Vector.h"
#include "Light.h"
#include <vector>

namespace vzl
{
	class ThingToHit;

	struct IntersectionData
	{
		double t = -1.0;
		const ThingToHit* geom = nullptr;
	};

	//
	class AABB
	{
		// courtesy of Dr. Jerry Tessendorf
	public:
		AABB(const Vector& lc, const Vector& uc);
		~AABB();

		const bool intersects(const AABB& aabb) const;
		AABB Intersection(const AABB& aabb) const;
		AABB Union(const AABB& aabb) const;
		void split(const int component, AABB& aabb1, AABB& aabb2) const;
		const double volume() const;
		const bool isInside(const Vector& P) const;
		const double intersect(const Vector& start, const Vector& direction) const;

		const Vector& LLC() const { return llc; }
		const Vector& URC() const { return urc; }
	private:
		Vector llc;
		Vector urc;
	};
	//

	class ThingToHit
	{
	public:
		ThingToHit() = delete;
		ThingToHit(const Color& color) : m_Color(color) { }
		virtual ~ThingToHit() { }

		virtual IntersectionData Intersection(const Ray& theRay) const = 0;
		virtual Color Shade(const Vector& point, const Light& light) const = 0;
		inline Color GetColor() const { return m_Color; }
		inline void SetColor(const Color& color) { m_Color = color; }

		inline void AddIgnoredLight(Light* light) { m_IgnoredLight.push_back(light); }
		bool IsIgnoredLight(Light* light) const;
		virtual const AABB aabb() const { return { {}, {} }; }

	protected:
		Color m_Color;
		std::vector<Light*> m_IgnoredLight;
	};

} // namespace vzl

#endif