/*#include "inputManager.h"


InputManager* InputManager::imInstance = NULL;

InputManager* InputManager::Instance() {

	if (imInstance == NULL) {
		imInstance = new InputManager();
	}

	return imInstance;

}

void InputManager::Release() {

	delete imInstance;
	imInstance = NULL;
}

InputManager::InputManager() {

}

InputManager::~InputManager() {

}

bool InputManager::KeyDown(SDL_Scancode scancode) {

	return mKeyboardStates[scancode];
	
}

void InputManager::Update() {

	mKeyboardStates = SDL_GetKeyboardState(NULL);

}
*/