#ifndef COLOR_HPP
#define COLOR_HPP
#include "SDL3/SDL.h"

namespace Utils {
	class Color {
		public:	
			
			Uint32 colorVal;

			Uint32 operator*(float alpha) const;
			Color(Uint32 colorVal);

		private:
			Uint32 blueBits;
			Uint32 redBits;
			Uint32 greenBits;
			Uint32 alphaBits;




	};
}





#endif