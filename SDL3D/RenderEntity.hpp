#ifndef RENDERENTITY_HPP
#define RENDERENTITY_HPP


#include "GameObject.hpp"
#include "Model.hpp"
#include "Camera.hpp"
#include "Texture.hpp"

namespace Entity {
	void renderEntity(Camera& camera, Model& model, GameObject& obj, RenderTools::Graphics& renderer, Entity::Texture &tex);
}


#endif