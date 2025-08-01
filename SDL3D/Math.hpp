#ifndef MATH_HPP
#define MATH_HPP

#include <vector>

namespace Math {
	
	std::vector<float> interpolateFloat(float i0, float d0, float i1, float d1);
	std::vector<int> interpolateInt(float i0, float d0, float i1, float d1);
	float toRad(float const degrees);


}



#endif