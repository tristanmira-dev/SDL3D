#ifndef MODEL_HPP
#define MODEL_HPP

#include "Vector3D.hpp"
#include "Vertex.hpp"
#include "Graphics.hpp"

#include <vector>
#include <initializer_list>


namespace Entity {
	class Model {
		public:
			/*Populate Vertex Container*/
			Model(std::initializer_list<Geometry::VertexData> listOfVertices);

			void insertTriangle(int idx1, int idx2, int idx3);

			void renderGameObj(RenderTools::Graphics &renderer);

			Geometry::TriangleContainer& getTriContainer();
		private:
			std::vector<Geometry::VertexData> vertexContainer;
			Geometry::TriangleContainer triContainer;
	};
}










#endif