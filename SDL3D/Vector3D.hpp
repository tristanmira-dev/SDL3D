#ifndef VECTOR3D_HPP
#define VECTOR3D_HPP

#include "Vector2D.hpp"

namespace Linear {
	class Vector3D : public Vector2D {

	public:
		float z;

		Vector3D(float x = 0.0f, float y = 0.0f, float z = 0.0f);
		Vector3D(Vector3D const& src) = default;

		virtual Vector3D& operator=(Vector3D const& src) = default;
		virtual Vector3D& operator+=(Vector3D const& src);
		virtual Vector3D operator+(Vector3D const& src);


		virtual Vector3D operator-(Vector3D const& vec) const;
		virtual bool operator==(Vector3D const& compare2);

	};

	Vector3D operator*(float const& val, Vector3D const& vec);
	Vector3D operator/(Vector3D const& vec, float const& val);


}



#endif