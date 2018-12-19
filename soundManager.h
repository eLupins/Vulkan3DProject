#include <SDL.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <iostream>
#include <string>


using namespace std;

typedef struct AudioData {

//	Mix_Music *gMusic = NULL;
	//Uint8* position;
	Uint64 id;
	Uint8 inUse;
	Uint32 length;
	std::string AUDIO_PATH;
	Mix_Chunk *sound;
	float volume;
}SoundSys;


void audioSys_init(Uint32 maxSounds, Uint32 channels, Uint32 channelGroups, Uint32 maxMusic, Uint8 enableMP3, Uint8 enableOGG);

void soundSys_init(Uint32 maxSounds);

SoundSys *soundNew();

SoundSys *sound_GetByFilePath(std::string *filepath);

SoundSys *soundLoad(std::string *filepath, float volume, int defaultchannel);

void soundPlay(SoundSys *sound, int numLoops, float volume, int channel, int group);

void sound_AdjustVolume(SoundSys *sound, float volume);

void soundFree(SoundSys *sound);

void soundDelete(SoundSys *sound);

void sound_DeleteAll();

