#ifndef PLANE_HPP
#define PLANE_HPP


#include "Vector3D.hpp"
#include "Vertex.hpp"
#include <unordered_map>


/*TODO HAVE AN EXTRA MEMBER VAR FOR PLANE COORDINATE*/

namespace Linear {
	const int oneTri{ 1 };
	const int twoTri{ 2 };
	const int zeroTri{ 0 };


	/*FOR CLIPPING*/
	enum CommonPlanesNormal {
		TOP,
		BOTTOM,
		LEFT,
		RIGHT,
		MIDDLE
	};

	struct Plane {
		Vector3D normal;
		Vector3D coord;
	};

	struct PlaneCollection {
		std::unordered_map<int, Plane> coll; /*COLLECTION OF NORMALS*/
	};

	Linear::Vector3D planeSegmIntersection(Plane const& plane, Linear::Vector3D pt0, Linear::Vector3D pt1);

	void setPlanes(float d, float fov, PlaneCollection& coll);

	float signedDistance(Plane const& plane, Vector3D const pt);

	int clipTri(Plane const& plane, Geometry::Triangle inputTri, Geometry::Triangle& tri1, Geometry::Triangle& tri2);
	

}







#endif