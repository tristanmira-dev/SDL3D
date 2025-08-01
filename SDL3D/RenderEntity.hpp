#ifndef RENDERENTITY_HPP
#define RENDERENTITY_HPP


#include "GameObject.hpp"
#include "Model.hpp"

namespace Entity {
	void renderEntity(Model &model, GameObject &obj, RenderTools::Graphics& renderer);


}


#endif