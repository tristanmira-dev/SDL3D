#ifndef MATH_HPP
#define MATH_HPP

#include "Color.hpp"
#include <vector>

namespace Math {
	
	std::vector<float> interpolateFloat(float i0, float d0, float i1, float d1);
	std::vector<int> interpolateInt(int i0, float d0, int i1, float d1);

	std::vector<Utils::Color> interpolateColor(int i0, Utils::Color d0, int i1, Utils::Color d1);
	float toRad(float const degrees);


}



#endif