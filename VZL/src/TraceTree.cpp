#include "ThingToHit.h"
#include <iostream>
#include "TraceTree.h"

namespace vzl
{
	TraceTree::TraceTree(const Vector & llc, const Vector & urc, const int lvl, const int maxlvl, const int minobj)
		: aabb(AABB(llc, urc)),
		  node1(0),
		  node2(0),
		  level(lvl),
		  max_levels(maxlvl),
		  min_objects(minobj),
		ThingToHit({1.0, 0.0, 0.0, 1.0})
	{
	}

	TraceTree::~TraceTree()
	{
		if (node1) { delete node1; }
		if (node2) { delete node2; }
	}

	void TraceTree::addObject(ThingToHit* o) 
	{ 
		object_list.push_back(o); 
	}

	void TraceTree::addObjects(const std::vector<ThingToHit*>& o)
	{
		for (size_t i = 0; i < o.size(); i++) { object_list.push_back(o[i]); }
	}

	IntersectionData TraceTree::Intersection(const Ray & theRay) const
	{
		return intersect(theRay.GetPosition(), theRay.GetDirection());
	}

	Color TraceTree::Shade(const Vector & point, const Light & light) const
	{
		// don't call this function!
		std::cout << "Warning!\n";
		return Color();
	}

	const IntersectionData TraceTree::intersect(const Vector& start, const Vector& direction) const
	{
		IntersectionData hit;
		if (aabb.isInside(start) || aabb.intersect(start, direction) >= 0.0)
		{
			if (node1 == 0 && node2 == 0)
			{
				// leaf level.  Intesection against object_list and return results
				for (size_t i = 0; i < object_list.size(); i++)
				{
					const double t = object_list[i]->Intersection({ start, direction }).t;
					if (t > 0.0)
					{
						if (hit.t < 0.0 || t < hit.t)
						{
							hit.t = t;
							hit.geom = object_list[i];
						}
					}
				}
				return hit;
			}
			else
			{
				if (node1 != 0 && node2 != 0)
				{
					const IntersectionData hit1 = node1->intersect(start, direction);
					const IntersectionData hit2 = node2->intersect(start, direction);
					if (hit1.t < 0.0 && hit2.t < 0.0) { return hit; }
					if (hit1.t > 0.0 && hit2.t < 0.0) { return hit1; }
					if (hit1.t < 0.0 && hit2.t > 0.0) { return hit2; }
					if (hit1.t < hit2.t)
					{
						return hit1;
					}
					else
					{
						return hit2;
					}
				}
				else if (node1 == 0)
				{
					return node2->intersect(start, direction);
				}
				else if (node2 == 0)
				{
					return node1->intersect(start, direction);
				}
			}
		}
		return hit;
	}

	void TraceTree::Divide()
	{
		//std::cout << "Dividing\n";
		if (level >= max_levels || object_list.size() <= (size_t)min_objects) { return; }

		AABB aabb1(aabb.LLC(), aabb.URC());
		AABB aabb2(aabb.LLC(), aabb.URC());
		aabb.split(level % 3, aabb1, aabb2);


		if (node1 != 0) { delete node1; }
		node1 = new TraceTree(aabb1.LLC(), aabb1.URC(), level + 1, max_levels, min_objects);
		// move objects into this node:
		for (size_t i = 0; i < object_list.size(); i++)
		{
			if (aabb1.intersects(object_list[i]->aabb()))
			{
				node1->addObject(object_list[i]);
			}
		}
		if (node1->nbObjects() == 0) { delete node1; node1 = 0; }

		if (node2 != 0) { delete node2; }
		node2 = new TraceTree(aabb2.LLC(), aabb2.URC(), level + 1, max_levels, min_objects);
		// move objects into this node:
		for (size_t i = 0; i < object_list.size(); i++)
		{
			if (aabb2.intersects(object_list[i]->aabb()))
			{
				node2->addObject(object_list[i]);
			}
		}
		if (node2->nbObjects() == 0) { delete node2; node2 = 0; }

		// double check that everyone is accounted for
		size_t totalobjects = 0;
		if (node1)
		{
			totalobjects += node1->nbObjects();
		}
		if (node2)
		{
			totalobjects += node2->nbObjects();
		}

		if (totalobjects < nbObjects())
		{
			std::cout << "TraceTree Divide mistake:  nb to be divided=" << nbObjects() << "   actual number " << totalobjects << std::endl;
		}
		object_list.clear();  // dont need this list anymore, so dont take up the space.
		if (node1) { node1->Divide(); }
		if (node2) { node2->Divide(); }
	}


}