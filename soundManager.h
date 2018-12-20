//#include <SDL.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <iostream>
#include <string>

#define FILEPATH_CHAR_LEN 512
#define MAX_SOUND_NUM 64
#define MAX_CHANNEL_NUM 4


using namespace std;

typedef struct AudioData {

//	Mix_Music *gMusic = NULL;
	//Uint8* position;
	Uint64 id;
	Uint8 inUse;
	Uint32 length;
	char AUDIO_PATH[FILEPATH_CHAR_LEN];
	Mix_Chunk *sound;
	int defaultChannel;
	float volume;

}SoundSys;


void audioSys_init(Uint32 maxSounds, Uint32 channels, Uint32 channelGroups, Uint32 maxMusic, Uint8 enableMP3, Uint8 enableOGG);

void soundSys_init(Uint32 maxSounds);

SoundSys *soundNew();

SoundSys *sound_GetByFilePath(const char *filepath);

SoundSys *soundLoad(const char *filepath, float volume, int defaultchannel);

void soundPlay(SoundSys *sound, int numLoops, float volume, int channel, int group);

void sound_AdjustVolume(SoundSys *sound, float volume);

void soundFree(SoundSys *sound);

void soundDelete(SoundSys *sound);

void sound_DeleteAll();

