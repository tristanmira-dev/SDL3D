#include "Matrix.hpp"
#include "Math.hpp"
#include "Graphics.hpp"

#include <algorithm>

#define _USE_MATH_DEFINES
#include <math.h>

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

	Matrix4x4 Matrix4x4::scaleMatrix(float x, float y, float z) {
		Matrix4x4 newScaleMatrix{};


		newScaleMatrix(0, 0) = x;
		newScaleMatrix(1, 1) = y;
		newScaleMatrix(2, 2) = z;
		newScaleMatrix(3, 3) = 1.f;

		return newScaleMatrix;
	}

	Matrix4x4 Matrix4x4::rotationYaw(float degrees) {
		float rad{ Math::toRad(degrees) };

		Matrix4x4 yawMtx{};

		yawMtx(0, 0) = cosf(rad);
		yawMtx(0, 2) = sinf(rad);
		yawMtx(1, 1) = 1.f;
		yawMtx(2, 0) = -sinf(rad);
		yawMtx(2, 2) = cosf(rad);
		yawMtx(3, 3) = 1.f;

		return yawMtx;
	}

	Matrix4x4 Matrix4x4::rotationPitch(float degrees) {
		float rad{ Math::toRad(degrees) };

		Matrix4x4 pitchMtx{};
		pitchMtx(0, 0) = 1.f;
		pitchMtx(1, 1) = cosf(rad);
		pitchMtx(1, 2) = -sinf(rad);
		pitchMtx(2, 1) = sinf(rad);
		pitchMtx(2, 2) = cosf(rad);
		pitchMtx(3, 3) = 1.f;

		return pitchMtx;
	}

	Matrix4x4 Matrix4x4::rotationRoll(float degrees) {
		float rad{ Math::toRad(degrees) };

		Matrix4x4 rollMtx{};
		rollMtx(0, 0) = cosf(rad);
		rollMtx(0, 1) = -sinf(rad);
		rollMtx(1, 0) = sinf(rad);
		rollMtx(1, 1) = cosf(rad);
		rollMtx(2, 2) = 1.f;
		rollMtx(3, 3) = 1.f;


		return rollMtx;
	}

	float& Matrix4x4::operator()(int row, int col) {
		return m[colSize * row + col];
	}

	float const& Matrix4x4::operator()(int row, int col) const {
		return m[colSize * row + col];
	}

	Vector3D Matrix4x4::operator*(Vector3D const& vec) {
		return Vector3D{
			(*this)(0, 0) * vec.x + (*this)(0, 1) * vec.y + (*this)(0, 2) * vec.z + (*this)(0, 3),
			(*this)(1, 0) * vec.x + (*this)(1, 1) * vec.y + (*this)(1, 2) * vec.z + (*this)(1, 3),
			(*this)(2, 0) * vec.x + (*this)(2, 1) * vec.y + (*this)(2, 2) * vec.z + (*this)(2, 3)
		};
	}

	Matrix4x4 Matrix4x4::operator*(Matrix4x4 const& mtx) {
		Matrix4x4 newMtx{};

		for (int y{}; y < rowSize; ++y) {
			for (int x{}; x < colSize; ++x) {
				float newVal{};
				for (int z{}; z < rowSize; ++z) {
					newVal += (*this)(y, z) * mtx(z, x);
				}
				newMtx(y, x) = newVal;
			}
		}
		return newMtx;
	}





}