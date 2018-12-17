/*
#define GLFW_INCLUDE_VULKAN
#include "vk_entity.h"
#include


void environmentSetup(std::string model_path, std::string texture_path, std::string entName, EntityType entType, int health) {

	ubo = ubo_New();
	ent = entity_new();

	ubo->TEXTURE_PATH = texture_path;
	ubo->TEXTURE_PATH.c_str();
	ubo->MODEL_PATH = model_path;
	ubo->MODEL_PATH.c_str();

	ent->entityObj = ubo;
	ent->entityType = entType;
	ent->health = health;
	ent->name = entName;
	createTextureImage(ent); //
	createTextureImageView();
	createTextureSampler();
	loadModel(ent);
}

void loadEnvironment(Entity ent) {

	if (ent.entityType != Environment) {
		throw std::runtime_error("LOADENVIRONMENT ERROR: ENTITY NOT OF TYPE ENVIRONMENT.");
	}

}
*/