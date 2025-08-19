#include "Plane.hpp"
#include "Math.hpp"
#include <utility>
#include <iostream>
#include <array>

namespace {

}

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

		planeColl.coll.insert(std::pair{ CommonPlanesNormal::TOP, Plane { Vector3D{topVector.x, -topVector.z, topVector.y}.normalize(), Vector3D{0.f, 0.f, 0.f} } });
		planeColl.coll.insert(std::pair{ CommonPlanesNormal::LEFT, Plane { Vector3D{leftVector.z, leftVector.y, -leftVector.x}.normalize(), Vector3D{0.f, 0.f, 0.f} } });
		planeColl.coll.insert(std::pair{ CommonPlanesNormal::RIGHT, Plane {Vector3D{-rightVector.z, rightVector.y, rightVector.x}.normalize() , Vector3D{0.f, 0.f, 0.f} } });
		planeColl.coll.insert(std::pair{ CommonPlanesNormal::BOTTOM, Plane { Vector3D{bottomVector.x, bottomVector.z, -bottomVector.y}.normalize(), Vector3D{0.f, 0.f, 0.f} } });
		planeColl.coll.insert(std::pair{ CommonPlanesNormal::MIDDLE, Plane {Vector3D{0.f, 0.f, 1.f}, Vector3D{0.f, 0.f, d}} });
	}

	float signedDistance(Plane const &plane, Vector3D const pt) {
		return plane.normal.dot(pt) - plane.normal.dot(plane.coord);
	}

	Linear::Vector3D planeSegmIntersection(Plane const& plane, Linear::Vector3D pt0, Linear::Vector3D pt1) {
	
		Linear::Vector3D lineSegm{ pt1 - pt0 };

		float t{ (plane.normal.dot(plane.coord) - plane.normal.dot(pt0)) / plane.normal.dot(lineSegm) };

		return Linear::Vector3D{ pt0 + t * lineSegm };
	
	}

	int clipTri(Plane const& plane, Geometry::Triangle inputTri, Geometry::Triangle& tri1, Geometry::Triangle& tri2) {
		

		float dist0{ signedDistance(plane, inputTri.vertices[0].coord) };
		float dist1{ signedDistance(plane, inputTri.vertices[1].coord) };
		float dist2{ signedDistance	(plane, inputTri.vertices[2].coord) };


		std::array<Geometry::VertexData*, 3> outsidePoints{};
		int totalOutside{};

		std::array<Geometry::VertexData*, 3> insidePoints{};
		int totalInside{};


		if ( dist0 >= 0.f && dist1 >= 0.f && dist2 >= 0.f) {
			tri1 = inputTri;
			return oneTri;
		} 

		if (dist0 < 0.f && dist1 < 0.f && dist2 < 0.f) {
			return zeroTri;
		}

		if (dist0 < 0.f) {
			outsidePoints[totalOutside++] = &(inputTri.vertices[0]);
		} else {
			insidePoints[totalInside++] = &(inputTri.vertices[0]);
		}

		if (dist1 < 0.f) {
			outsidePoints[totalOutside++] = &(inputTri.vertices[1]);
		} else {
			insidePoints[totalInside++] = &(inputTri.vertices[1]);
		}

		if (dist2 < 0.f) {
			outsidePoints[totalOutside++] = &(inputTri.vertices[2]);
		} else {
			insidePoints[totalInside++] = &(inputTri.vertices[2]);
		}


		if (totalInside == 1) {
			Geometry::VertexData pt01{ planeSegmIntersection(plane, insidePoints[0]->coord, outsidePoints[0]->coord), 1.f, 0xFF0000FF };
			Geometry::VertexData pt02{ planeSegmIntersection(plane, insidePoints[0]->coord, outsidePoints[1]->coord), 1.f, 0xFF0000FF };


			tri1.vertices = Geometry::Vertices{ *(insidePoints[0]), pt01, pt02 };


			return oneTri;
		}

		if (totalInside == 2) {
			Geometry::VertexData pt02{ planeSegmIntersection(plane, insidePoints[0]->coord, outsidePoints[0]->coord), 1.f, 0xFF0000FF };
			Geometry::VertexData pt12{ planeSegmIntersection(plane, insidePoints[1]->coord, outsidePoints[0]->coord), 1.f, 0xFF0000FF };

			tri1.vertices = Geometry::Vertices{ *(insidePoints[0]), *(insidePoints[1]), pt02 };
			tri2.vertices = Geometry::Vertices{ *(insidePoints[1]), pt12, pt02 };

			return twoTri;
		}


		return zeroTri;
	}

}