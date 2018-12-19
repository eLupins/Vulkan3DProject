#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vulkan/vulkan.h>
#include <string>


///needed to make an ubo
typedef struct UniformBufferObject {

	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 proj;
	//const std::string MERCHDOG_PATH = "models/merchdog.obj"; // change this when you skin & rig merchant dog
//	const std::string TEXTURE_PATH = "textures/plastic.png";
	std::string MODEL_PATH; //model path; provide explorer paath
	std::string TEXTURE_PATH; //texture path; provide explorer path
	int inUse;
	//std::vector<Vertex> vertices;
//	std::vector<uint32_t> indices;

}Ubo;


typedef struct UboManager {

	Ubo *uboList;
	int numEntity;
	int numSwapChain;
	int numUbo;


} UboManager;



Ubo* ubo_New();
void ubomanagerInit(int numUbos, int numEnt, int numSwapChain);