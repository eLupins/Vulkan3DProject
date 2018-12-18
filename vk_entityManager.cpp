#include "vk_entity.h"
//#include "vk_uniform_buffer_object.h"

//struct for our EntityManager
typedef struct entityManager_s {

	uint32_t maxEnt;
	Entity *entityList;
	uint64_t increment;
//	UniformBufferObject *uboList;

}EntitySysManager;


static EntitySysManager entityManager = { 0, nullptr , 0 };

//used to stop the entity system and 
void entity_system_close() {
	
	int i = 0;
	
	if (entityManager.entityList != NULL) {
		for (i = 0; i < entityManager.maxEnt; i++) {
			entity_free(&entityManager.entityList[i]);
		}
		free(entityManager.entityList);
	}
	memset(&entityManager, 0, sizeof(entityManager));
	std::printf("ENTITY SYSTEM CLOSED");
}
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
//initializing the entity system
void entity_system_init(uint32_t maxEntities) {

	if (maxEntities <= 0) {
		throw std::runtime_error("CANNOT INITIALIZE MANAGER FOR ZERO OR NEGATIVE ENTITIES");
	}
	
	memset(&entityManager, 0, sizeof(entityManager)); //setting memory for entitymanager
	entityManager.entityList = (Entity*)(malloc(sizeof(Entity) * maxEntities)); //malloc memory for entitylist

	if (!entityManager.entityList) {
		throw std::runtime_error("UNABLE TO ALLOCATE MEMORY FOR ENTITYLIST");
	}
	
	memset(entityManager.entityList, 0, sizeof(Entity) * maxEntities); //set memory for entitylist
	entityManager.maxEnt = maxEntities;

	std::printf("SUCCESSFUL: INITIALIZED ENTITY SYSTEM\n" );
	atexit(entity_system_close); // inititiate systemclose at the end of the program
}


//adding entities
Entity *entity_new() {

	Ubo ubo;

	for (int i = 0; i < entityManager.maxEnt; i++) {
		if (entityManager.entityList[i].inUse == 0) { //check to see if the entity on the list is in use 

			//if it is, set the memory to 0 just in case theres garbage data
			memset(&entityManager.entityList[i], 0, sizeof(Entity));
			//then make the entity's id the increment
			entityManager.entityList[i].id = entityManager.increment++;
			entityManager.entityList[i].inUse = 1; 
			//set the entity to inuse

			//figure out how you structured the ubos before making a line for ubos
			//a line for reference::: entityManager.entityList[i].ubo = uniforms_get_local_reference(gf3d_vgraphics_get_uniform_buffer_manager(), i, 0);
			return &entityManager.entityList[i];
		}
	}
}


//freeing an entity from memory 
void entity_free(Entity *e) {

	//if the pointer to entity is null, then return this
	if (!e) {
		throw std::runtime_error("CANNOT FREE AN ENTITY THAT IS NULL.");
		return;
	}

	//if the pointer to the entity isn't null, free the entity from memory
	if (e->free) {
		e->free(e);
	}
	memset(e, 0, sizeof(Entity));
}


//freeing ALLLLL the entities
void entity_free_all() {

	for (int i = 0; i < entityManager.maxEnt; i++) {
		entity_free(&entityManager.entityList[i]);
	}
}


//update function
void entity_update(Entity *self) {

	//you'll have to figure out the generic entity functions to yourself depending on how you want your entity to move about.

	//if there is no entity, then run this
	if (!self) {
		throw std::runtime_error("CANNOT UPDATE AN ENTITY THAT DOESN'T EXIST");
	}

	//if entity's inuse is 0, then run this
	if (self->inUse == 0) {
		throw std::runtime_error("CANNNOT UPDATE AN ENTITY THAT IS NOT IN USE");
	}

	//if entity has an update, then run its update function
	if (self->update) {
		self->update(self);
	}

}

//update ALLLLL the entities
void entity_update_all() {

	for (int i = 0; i < entityManager.maxEnt; i++) {
		if (entityManager.entityList->inUse == 1) {

			entity_update(&entityManager.entityList[i]);
		
		}
	}
}
/*
bool CheckCollision() {

	

}*/