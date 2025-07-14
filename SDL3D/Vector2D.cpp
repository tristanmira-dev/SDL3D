#include "Vector2D.hpp"

namespace Linear {
	/*CONSTRUCTORS*/
	Vector2D::Vector2D(float x, float y) : x{ x }, y{ y } { /*EMPTY*/ }


	/*OPERATOR OVERLOADS*/
	Vector2D& Vector2D::operator+=(Vector2D const& src) {
		this->x += src.x;
		this->y += src.y;

		return *this;
	}

	Vector2D Vector2D::operator+(Vector2D const& src) {
		return Vector2D{ this->x + src.x, this->y + src.y };
	}

	Vector2D Vector2D::operator-(Vector2D const& vec) const {
		return Vector2D{ this->x - vec.x, this->y - vec.y };
	}

	bool Vector2D::operator==(Vector2D const& compare2) {
		return this->x == compare2.x && this->y == compare2.y;
	}

	Vector2D operator*(float const& val, Vector2D const& vec) {
		return Vector2D{ val * vec.x, val * vec.y };
	}

	Vector2D operator/(Vector2D const& vec, float const& val) {
		return Vector2D{ vec.x / val, vec.y / val };
	}


}