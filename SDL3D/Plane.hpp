#ifndef PLANE_HPP
#define PLANE_HPP


#include "Vector3D.hpp"
#include <unordered_map>

namespace Linear {

	/*FOR CLIPPING*/
	enum CommonPlanesNormal {
		TOP,
		BOTTOM,
		LEFT,
		RIGHT,
		MIDDLE
	};

	struct PlaneCollection {
		std::unordered_map<int, Vector3D> coll; /*COLLECTION OF NORMALS*/
	};

	void setPlanes(float d, float fov, PlaneCollection& coll);

}







#endif