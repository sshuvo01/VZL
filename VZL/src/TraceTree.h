#ifndef ___TRACETREE_H____
#define ___TRACETREE_H____
/*
// Courtesy of Dr. Jerry Tessendorf
*/

#include "Vector.h"
#include "ThingToHit.h"

namespace vzl {

	class TraceTree : public ThingToHit
	{
	public:

		TraceTree(const Vector& llc, const Vector& urc, const int lvl, const int maxlvl, const int minobj);
		~TraceTree();

		void Divide();

		void addObject(ThingToHit* o);
		void addObjects(const std::vector<ThingToHit*>& o);

		IntersectionData Intersection(const Ray& theRay) const override;
		Color Shade(const Vector& point, const Light& light) const override;

		const IntersectionData intersect(const Vector& start, const Vector& direction) const;

		const size_t nbObjects() const { return object_list.size(); }

	private:

		AABB aabb;
		TraceTree* node1;
		TraceTree* node2;

		int level;
		int max_levels;
		int min_objects;

		std::vector<ThingToHit*> object_list;
	};


}

#endif
