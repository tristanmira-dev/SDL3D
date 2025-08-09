#include "Plane.hpp"
#include "Math.hpp"
#include <utility>

namespace Linear {



	void setPlanes(float d, float fov, PlaneCollection& planeColl) {
		float theta{ fov / 2.f };
		theta = Math::toRad(theta);


		float opp{std::tanf(theta) * d};
		Vector3D leftVector{ -opp, 0.f, d };
		Vector3D rightVector{ opp, 0.f, d };
		Vector3D topVector{0.f, opp, d };
		Vector3D bottomVector{ 0.f, -opp, d };

		planeColl.coll.insert(std::pair{ CommonPlanesNormal::TOP, Vector3D{topVector.x, topVector.z, -topVector.y} });
		planeColl.coll.insert(std::pair{ CommonPlanesNormal::LEFT, Vector3D{leftVector.z, leftVector.y, -leftVector.x} });
		planeColl.coll.insert(std::pair{ CommonPlanesNormal::RIGHT, Vector3D{rightVector.z, rightVector.y, -rightVector.x} });
		planeColl.coll.insert(std::pair{ CommonPlanesNormal::BOTTOM, Vector3D{bottomVector.x, bottomVector.z, -bottomVector.y} });
		planeColl.coll.insert(std::pair{ CommonPlanesNormal::MIDDLE, Vector3D{0.f, 0.f, 1.f} });
	}

}