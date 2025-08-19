#ifndef COLOR_HPP
#define COLOR_HPP
#include "SDL3/SDL.h"

namespace Utils {
	class Color {
		public:	
			
			Uint32 colorVal;

			Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
			Color(Uint32 colorVal);


			Uint8 r();
			Uint8 g();
			Uint8 b();
			Uint8 a();


			Uint32 operator*(float alpha) const;

		private:
			Uint32 blueBits;
			Uint32 redBits;
			Uint32 greenBits;
			Uint32 alphaBits;




	};
}





#endif