#include "Matrix.hpp"
#include "Math.hpp"
#include "Graphics.hpp"

#include <algorithm>

namespace {
	const int rowSize{ 4 };
	const int colSize{ 4 };
}


namespace Linear {

	//Vector3D Vector3D::project(RenderTools::Graphics const& renderer) {
	//	float pX{ x / z };
	//	float pY{ y / z };

	//	float viewport{ 2 * tanf(Math::toRad(40.f)) };

	//	float cX{ (pX / viewport) * renderer.getWidth() };
	//	float cY{ (pY / viewport) * renderer.getHeight() };



	//	return Vector3D{ cX, cY, 1.f };



	//}

	Matrix4x4::Matrix4x4() {
		std::fill(m, m + (rowSize * colSize), 0.f);
	}

	/*Matrix4x4 Matrix4x4::projectionMatrix(float fov, float distance, RenderTools::Graphics const &renderer) {

		float viewportHW{ 2 * tanf(Math::toRad(40.f)) };



		return Matrix4x4{
					

		}
	}*/

	Matrix4x4 Matrix4x4::translateMatrix(float x, float y, float z) {
		Matrix4x4 translationMatrix{};


		translationMatrix(0, 0) = 1.f;
		translationMatrix(1, 1) = 1.f;
		translationMatrix(2, 2) = 1.f;
		translationMatrix(3, 3) = 1.f;


		translationMatrix(0, 3) = x;
		translationMatrix(1, 3) = y;
		translationMatrix(2, 3) = z;


		return translationMatrix;
	}

	float& Matrix4x4::operator()(int row, int col) {
		return m[colSize * row + col];
	}

	Vector3D Matrix4x4::operator*(Vector3D const& vec) {
		return Vector3D{
			(*this)(0, 0) * vec.x + (*this)(0, 1) * vec.y + (*this)(0, 2) * vec.z + (*this)(0, 3),
			(*this)(1, 0) * vec.x + (*this)(1, 1) * vec.y + (*this)(1, 2) * vec.z + (*this)(1, 3),
			(*this)(2, 0) * vec.x + (*this)(2, 1) * vec.y + (*this)(2, 2) * vec.z + (*this)(2, 3)
		};
	}





}