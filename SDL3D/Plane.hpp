#ifndef PLANE_HPP
#define PLANE_HPP


#include "Vector3D.hpp"
#include "Vertex.hpp"
#include <unordered_map>


/*TODO HAVE AN EXTRA MEMBER VAR FOR PLANE COORDINATE*/

namespace Linear {

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

	void setPlanes(float d, float fov, PlaneCollection& coll);

	float signedDistance(Vector3D const planeNormal, Vector3D const pt);

	Geometry::TriangleContainer clipTri();
	

}







#endif