/*
#ifndef _INPUTMANAGER_H
#define _INPUTMANAGER_H
#include <SDL.h>

class InputManager{

private:
	static InputManager* imInstance;
	const Uint8* mKeyboardStates;
	
public:
	static InputManager* Instance();
	static void Release();
	bool KeyDown(SDL_Scancode scancode);
	void Update();

private:
	InputManager();
	~InputManager();

};

#endif
*/