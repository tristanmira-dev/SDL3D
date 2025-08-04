#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "Vector3D.hpp"

namespace Linear {

	class Matrix4x4 {
		public:
			Matrix4x4();
			//Matrix4x4 projectionMatrix(float fov, float distance, RenderTools::Graphics const& renderer);

			static Matrix4x4 translateMatrix(float x, float y, float z);
			static Matrix4x4 scaleMatrix(float x, float y, float z);
			static Matrix4x4 rotationPitch(float degrees);
			static Matrix4x4 rotationRoll(float degrees);
			static Matrix4x4 rotationYaw(float degrees);

			float& operator()(int row, int col);
			float const& operator()(int row, int col) const;

			Vector3D operator*(Vector3D const &vec);

			Matrix4x4 operator*(Matrix4x4 const &mtx);

		private:
			float m[16];

	};

}





#endif