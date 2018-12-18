#include <SDL.h>
#include <vector>
#include "gf3d_vector.h"
#include <glm/glm.hpp>

//Referencing EngineerofLies code to try and learn: https://github.com/engineerOfLies/gameframework2d/tree/particles

typedef enum {

	Sprite,

}ParticleTypes;


struct particleSys {

	Uint8 inUse;
	float life;
	glm::vec2 position, velocity;
	glm::vec4 color;
	ParticleTypes particleType;
	std::string PARTICLE_PATH;
	

	SDL_BlendMode mode;

	particleSys()
		: position(0.0f), velocity(0.0f), color(1.0f), life(0.0f) { }

};
