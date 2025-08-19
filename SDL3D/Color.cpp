#include "Color.hpp"
#include "SDL3/SDL.h"

namespace Utils {
	Color::Color(Uint32 colorVal) : colorVal{ colorVal }, blueBits{0x0000FF00}, redBits{0xFF000000}, greenBits{0x00FF0000}, alphaBits {0x000000FF} {}

	Uint8 Color::r() {
		return static_cast<Uint8>((colorVal & redBits) >> 24);
	}

	Uint8 Color::g() {
		return static_cast<Uint8>((colorVal & greenBits) >> 16);
	}

	Uint8 Color::b() {
		return static_cast<Uint8>((colorVal & blueBits) >> 8);
	}

	Uint8 Color::a() {
		return static_cast<Uint8>((colorVal & alphaBits));
	}


	Uint32 Color::operator*(float alpha) const {
		Uint8 const r{ static_cast<Uint8>(alpha * ((colorVal & redBits) >> 24)) };
		Uint8 const g{ static_cast<Uint8>(alpha * ((colorVal & greenBits) >> 16)) };
		Uint8 const b{ static_cast<Uint8>(alpha * ((colorVal & blueBits) >> 8)) };
		Uint8 const a{ static_cast<Uint8>(colorVal & alphaBits) };

		return static_cast<Uint32>(r << 24) | static_cast<Uint32>(g << 16) | static_cast<Uint32>(b << 8) | static_cast<Uint32>(a);
	}

	Color::Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a) : colorVal{}, blueBits { 0x0000FF00 }, redBits{ 0xFF000000 }, greenBits{ 0x00FF0000 }, alphaBits{ 0x000000FF } {
		Uint32 newR{ static_cast<Uint32>(r << 24) };
		Uint32 newG{ static_cast<Uint32>(g << 16) };
		Uint32 newB{ static_cast<Uint32>(b << 8) };
		Uint32 newA{ static_cast<Uint32>(a) };

		this->colorVal = newR | newG | newB | newA;
	}

}

