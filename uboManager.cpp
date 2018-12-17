#include "vk_uniform_buffer_object.h"

UboManager uboManager = {nullptr, 0, 0, 0};

void ubomanagerInit(int numUbos, int numEnt, int numSwapChain) {

	memset(&uboManager, 0, sizeof(uboManager));
	uboManager.uboList = (Ubo*)(malloc(sizeof(Ubo) * numUbos));
	memset(uboManager.uboList, 0, sizeof(Ubo) * numUbos);
	uboManager.numUbo = numUbos;
	uboManager.numEntity = numEnt;
	uboManager.numSwapChain = numSwapChain;


}


Ubo* ubo_New() {

//	Ubo ubo;

	for (int i = 0; i < uboManager.numUbo; i++) {

		if (uboManager.uboList[i].inUse == 0) {
		
			memset(&uboManager.uboList[i], 0, sizeof(Ubo));
			uboManager.uboList[i].inUse = 1;

			return &uboManager.uboList[i];
		
		}
	}
}

