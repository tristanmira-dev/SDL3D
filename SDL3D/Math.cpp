#include "Math.hpp"

namespace Math {
	std::vector<int> interpolateInt(float i0, float d0, float i1, float d1) {

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

	std::vector<float> interpolateFloat(float i0, float d0, float i1, float d1) {

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


