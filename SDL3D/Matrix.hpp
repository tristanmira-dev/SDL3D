#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "Vector3D.hpp"

namespace Linear {

	class Matrix4x4 {
		public:
			Matrix4x4();
			//Matrix4x4 projectionMatrix(float fov, float distance, RenderTools::Graphics const& renderer);

			static Matrix4x4 translateMatrix(float x, float y, float z);

			float& operator()(int row, int col);

			Vector3D operator*(Vector3D const &vec);

		private:
			float m[16];

	};

}





#endif