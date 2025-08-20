#include "Math.hpp"

#define _USE_MATH_DEFINES
#include <math.h>

#include <iostream>

namespace Math {
	std::vector<int> interpolateInt(int i0, float d0, int i1, float d1) {

		if (i0 == i1) {
			return std::vector<int> { static_cast<int>(d0) };
		}

		float a{ (d1 - d0) / (i1 - i0) };
		float c{ d0 };

		std::vector<int> values{};

		for (int x{ static_cast<int>(i0) }; x <= i1; ++x) {

			values.emplace_back(static_cast<int>(c));
			c += a;
		}


		return values;
	}

	std::vector<Utils::Color> interpolateColor(int i0, Utils::Color d0, int i1, Utils::Color d1) {

		if (i0 == i1) {
			return std::vector<Utils::Color> { d0  };
		}

		float rA{ (static_cast<float>(d1.r()) - d0.r()) / (i1 - i0) };
		float rC{ static_cast<float>(d0.r()) };

		float gA{ (static_cast<float>(d1.g()) - d0.g()) / (i1 - i0) };
		float gC{ static_cast<float>(d0.g()) };

		float bA{ (static_cast<float>(d1.b()) - d0.b()) / (i1 - i0) };
		float bC{ static_cast<float>(d0.b()) };

		float aA{ (static_cast<float>(d1.a()) - d0.a()) / (i1 - i0) };
		float aC{ static_cast<float>(d0.a()) };

		std::vector<Utils::Color> values{};

		for (int x{ static_cast<int>(i0) }; x <= i1; ++x) {

			values.emplace_back(Utils::Color{ static_cast<Uint8>(rC), static_cast<Uint8>(gC), static_cast<Uint8>(bC), static_cast<Uint8>(aC) });
			rC += rA;

			gC += gA;

			bC += bA;

			aC += aA;
		}


		return values;
	}

	float toRad(float const degrees) {
		return degrees * (static_cast<float>(M_PI) / 180.f);
	}

	std::vector<float> interpolateFloat(int i0, float d0, int i1, float d1) {

		if (i0 == i1) {
			return std::vector<float> { d0 };
		}

		float a{ (d1 - d0) / (i1 - i0) };
		float c{ d0 };

		std::vector<float> values{};

		for (int x{ static_cast<int>(i0) }; x <= i1; ++x) {
			values.emplace_back(c);
			c += a;
		}


		return values;
	}
}


