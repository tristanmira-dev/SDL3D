#ifndef VECTOR2D_HPP
#define VECTOR2D_HPP
	

namespace Linear {
	class Vector2D {

		public:
			float x;
			float y;

			Vector2D(float x = 0.0f, float y = 0.0f);
			Vector2D(Vector2D const& src) = default;

			virtual Vector2D& operator=(Vector2D const& src) = default;
			virtual Vector2D& operator+=(Vector2D const& src);
			virtual Vector2D operator+(Vector2D const& src);


			virtual Vector2D operator-(Vector2D const& vec) const;
			virtual bool operator==(Vector2D const& compare2);

	};

	Vector2D operator*(float const& val, Vector2D const& vec);
	Vector2D operator/(Vector2D const& vec, float const& val);


}



#endif