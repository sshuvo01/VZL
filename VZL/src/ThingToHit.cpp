#include "ThingToHit.h"
#include <algorithm>

namespace vzl
{


	bool ThingToHit::IsIgnoredLight(Light* light) const
	{
		auto iter = std::find(m_IgnoredLight.begin(), m_IgnoredLight.end(), light);
		return iter != m_IgnoredLight.end();
	}

	// courtesy of Dr. Jerry Tessendorf
	AABB::AABB(const Vector& lc, const Vector& uc) :
		llc(lc),
		urc(uc)
	{}

	AABB::~AABB() {}

	const bool AABB::intersects(const AABB& aabb) const
	{
		if (llc[0] > aabb.urc[0]) { return false; }
		if (llc[1] > aabb.urc[1]) { return false; }
		if (llc[2] > aabb.urc[2]) { return false; }
		if (aabb.llc[0] > urc[0]) { return false; }
		if (aabb.llc[1] > urc[1]) { return false; }
		if (aabb.llc[2] > urc[2]) { return false; }
		return true;
	}

	AABB AABB::Intersection(const AABB& aabb) const
	{
		Vector nllc = llc;
		Vector nurc = urc;
		if (!intersects(aabb)) { return AABB(nllc, nllc); }
		for (int i = 0; i < 2; i++)
		{
			if (llc[i] < aabb.llc[i]) { nllc[i] = aabb.llc[i]; }
			if (urc[i] > aabb.urc[i]) { nurc[i] = aabb.urc[i]; }
		}
		return AABB(nllc, nurc);
	}

	AABB AABB::Union(const AABB& aabb) const
	{
		Vector nllc = llc;
		Vector nurc = urc;
		for (int i = 0; i < 3; i++)
		{
			if (nllc[i] > aabb.llc[i]) { nllc[i] = aabb.llc[i]; }
			if (nurc[i] < aabb.urc[i]) { nurc[i] = aabb.urc[i]; }
		}
		return AABB(nllc, nurc);
	}


	void AABB::split(const int component, AABB& aabb1, AABB& aabb2) const
	{
		Vector center = (llc + urc)*0.5;
		Vector split_plane = llc;
		split_plane[component] = center[component];
		aabb1.llc = split_plane;
		aabb1.urc = urc;
		split_plane = urc;
		split_plane[component] = center[component];
		aabb2.llc = llc;
		aabb2.urc = split_plane;
	}

	const double AABB::volume() const
	{
		Vector diff = urc - llc;
		return diff[0] * diff[1] * diff[2];
	}

	const bool AABB::isInside(const Vector& P) const
	{
		for (int i = 0; i < 3; i++)
		{
			if (P[i] < llc[i]) { return false; }
			if (P[i] > urc[i]) { return false; }
		}
		return true;
	}

	const double AABB::intersect(const Vector& start, const Vector& direction) const
	{
		// Smits method ala Shirley document
		double tmin, tmax, tymin, tymax, tzmin, tzmax;
		double divx = 1.0 / direction[0];
		double divy = 1.0 / direction[1];
		double divz = 1.0 / direction[2];
		if (divx >= 0)
		{
			tmin = (llc[0] - start[0]) * divx;
			tmax = (urc[0] - start[0]) * divx;
		}
		else
		{
			tmin = (urc[0] - start[0]) * divx;
			tmax = (llc[0] - start[0]) * divx;
		}
		if (divy >= 0)
		{
			tymin = (llc[1] - start[1]) * divy;
			tymax = (urc[1] - start[1]) * divy;
		}
		else
		{
			tymin = (urc[1] - start[1]) * divy;
			tymax = (llc[1] - start[1]) * divy;
		}
		if ((tmin > tymax) || (tymin > tmax)) { return -1.0; }
		if (tymin > tmin) { tmin = tymin; }
		if (tymax < tmax) { tmax = tymax; }
		if (divz >= 0)
		{
			tzmin = (llc[2] - start[2]) * divz;
			tzmax = (urc[2] - start[2]) * divz;
		}
		else
		{
			tzmin = (urc[2] - start[2]) * divz;
			tzmax = (llc[2] - start[2]) * divz;
		}
		if ((tmin > tzmax) || (tzmin > tmax)) { return -1.0; }
		if (tzmin > tmin) { tmin = tzmin; }
		if (tmin < 0 || isnan(tmin)) { tmin = -1.0; }
		return tmin;
	}


} // namespace vzl