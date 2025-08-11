#include "Plane.hpp"
#include "Math.hpp"
#include <utility>

namespace Linear {


	/*SET THE 5 PLANES ACCORDING TO */
	void setPlanes(float d, float fov, PlaneCollection& planeColl) {
		float theta{ fov / 2.f };
		theta = Math::toRad(theta);


		float opp{std::tanf(theta) * d};
		Vector3D leftVector{ -opp, 0.f, d };
		Vector3D rightVector{ opp, 0.f, d };
		Vector3D topVector{0.f, opp, d };
		Vector3D bottomVector{ 0.f, -opp, d };

		planeColl.coll.insert(std::pair{ CommonPlanesNormal::TOP, Plane { Vector3D{topVector.x, topVector.z, -topVector.y}.normalize(), Vector3D{} } });
		planeColl.coll.insert(std::pair{ CommonPlanesNormal::LEFT, Plane { Vector3D{leftVector.z, leftVector.y, -leftVector.x} .normalize(), Vector3D{} } });
		planeColl.coll.insert(std::pair{ CommonPlanesNormal::RIGHT, Plane {Vector3D{rightVector.z, rightVector.y, -rightVector.x}.normalize() , Vector3D{} } });
		planeColl.coll.insert(std::pair{ CommonPlanesNormal::BOTTOM, Plane { Vector3D{bottomVector.x, bottomVector.z, -bottomVector.y}.normalize(), Vector3D{} } });
		planeColl.coll.insert(std::pair{ CommonPlanesNormal::MIDDLE, Plane {Vector3D{0.f, 0.f, 1.f}, Vector3D{0.f, 0.f, d}} });
	}

	float signedDistance(Vector3D const planeNormal, Vector3D const pt) {
		return planeNormal.dot(pt) + planeNormal.dot(Vector3D{0.f, 0.f, 2.f});
	}

	Geometry::TriangleContainer clipTri() {
		return Geometry::TriangleContainer();
	}

}