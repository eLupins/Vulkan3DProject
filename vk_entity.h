//#include <glm/glm.hpp>
#include <tiny_obj_loader.h>
//#include <glm/gtc/matrix_transform.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include "vk_uniform_buffer_object.h"

enum EntityType {

	Blank = 0, //any default entity that isnt assigned a type will be type blank
	Player = 1 ,
	Bullets = 2,
	Enemy = 3,
	Items = 4,

};

typedef struct entity_s {

	////Indetitfiers////
	uint32_t id;
	std::string name;
	short unsigned int inUse;
	EntityType entityType;

	//physics
	glm::vec3 pos;
	glm::vec3 rotation;
	glm::vec3 velocity;
	glm::vec3 acceleration;
	uint8_t testNum;

	int health;

	//mesh data
	Ubo *entityObj; //this includes model, view, proj, modelpath, and texture path

	//function pointers for logic
	void(*draw)(struct entity_s *self); //your own draw function (draw frame????)
	void(*update)(struct entity_s *self); //your own update function
	void(*die)(struct entity_s *self); 
	void(*free)(struct entity_s *self); //freeing memory
	void(*attack)(struct entity_s *self); //attack function

}Entity;

/*
*@brief Closes the Entity System, automatically called in entity_system_init atexit()
*/
void entity_system_close();


/**
* @brief Initializes the Entity Manager
* @param maxEntities The maximum number of entities that can exist at once
*/
void entity_system_init(uint32_t maxEntities);

/**
* @brief Finds an spot in the Entity Manager that is not in use and returns its address
* @returns An address in memory for the new entity if successful; NULL if failed
*/
Entity *entity_new();

/**
* @brief Creates a new entity with specified attributes
* @param modelFilename The filename of the model to assign to the entity
* @returns A pointer to the new entity
*/
//Entity *entity_load(char *modelFilename);

/**
* @brief Recycles an entity slot back to the Entity Manager
* @param e The entity to free
*/
void entity_free(Entity *e);

/**
* @brief Recycles all entities in the Entity Manager without closing the system
*/
void entity_free_all();

/**
* @brief Runs generic updates on an update, plus any extra function if an entity has one
* @param self The entity to update
*/
void entity_update(Entity *self);

/**
* @brief Runs entity_update on every existing entity
*/
void entity_update_all();