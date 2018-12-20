#include "soundManager.h"

typedef struct SoundManager {

	Uint32 maxSounds;
	SoundSys *soundList;
	Uint64 i;
	Uint8 initialize;

}soundM;


static soundM soundManager = { 0, NULL, 0, 0 };


void audioSys_close() {

	int x = 0;
	if (soundManager.soundList != NULL) {
		for (x = 0; x < soundManager.maxSounds; x++) {

			soundFree(&soundManager.soundList[x]);
			
		}
		free(&soundManager.soundList);
	}

	memset(&soundManager, 0, sizeof(soundManager));
	std::printf("SOUND MANAGER CLOSED.\n");
}


void audioSys_init(Uint32 maxSounds, Uint32 channels, Uint32 channelGroups, Uint32 maxMusic, Uint8 enableMP3, Uint8 enableOGG) {

	int flags = 0;

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
		printf("ERROR: CANNOT INITIALIZE AUDIO SYSTEM.\n", SDL_GetError);
		return;
	}

	if (enableMP3) {
		flags |= MIX_INIT_MP3;
	}

	if (enableOGG) {
		flags |= MIX_INIT_OGG;
	}

	if (!(Mix_Init(flags) & flags)) {
		throw std::runtime_error("FAILED TO INITIALIZE SOME AUDIO SUPPORT\n");
	}

	Mix_AllocateChannels(channels);

	if (soundManager.initialize == 0) {
		soundSys_init(maxSounds);
	}

	atexit(Mix_Quit);
	atexit(audioSys_close);
}

void soundSys_init(Uint32 maxSounds) {

	if (maxSounds <= 0) {
		printf("CANNOT INITIALIZE A SOUND MANAGER FOR NO SOUNDS\n");
		return;
	}

	memset(&soundManager, 0, sizeof(soundManager));
	soundManager.soundList = (SoundSys *)malloc(sizeof(SoundSys)* maxSounds);

	if (!soundManager.soundList) {
		printf("ERROR: DID NOT SUCCESSFULLY ALLOCATE MEMORY FOR THE SOUND LIST");
		audioSys_close();
		return;
	}
	
	memset(soundManager.soundList, 0, sizeof(SoundSys) * maxSounds);
	soundManager.maxSounds = maxSounds;
	soundManager.initialize = 1;

	printf("SUCCESSFUL: INITIALIZED SOUND SYSTEM.\n");
	atexit(audioSys_close);

}


SoundSys *soundNew() {

	int x = 0;

	for (x = 0; x < soundManager.maxSounds; x++) {
		if (soundManager.soundList[x].inUse == 0) {
			memset(&soundManager.soundList[x], 0, sizeof(SoundSys));
			soundManager.soundList[x].id = soundManager.i++;
			soundManager.soundList[x].inUse = 1;
			return &soundManager.soundList[x];
		}
	}
	printf("ERROR: NO SPACE FOR ADDITIONAL SOUND\n");
	return NULL;
}

SoundSys *sound_GetFileByPath(const char *filepath) {

	int x = 0;

	for (x = 0; x < soundManager.maxSounds; x++) {
		if (strncmp(soundManager.soundList[x].AUDIO_PATH, filepath, FILEPATH_CHAR_LEN) == 0)
		{
			return &soundManager.soundList[x];
		}
	}

	printf("ERROR: INVALID FILE PATH\n");
	return NULL;
}

SoundSys *soundLoad (const char *filepath, float volume, int defaultChannel) {

	SoundSys *sound;

	if (!filepath) {
		printf("ERROR: EMPTY FILEPATH\n");
		return NULL;
	}

	sound = sound_GetFileByPath(filepath);
	if (sound) {
		sound->inUse = 1;
		return sound;
	}

	sound = soundNew();
	sound->sound = Mix_LoadWAV(filepath);
	
	if (!sound->sound) {
		printf("FAILED TO LOAD SOUND FILE\n");
		soundFree(sound);
		return NULL;
	}

	sound->volume = volume;
	sound->defaultChannel = defaultChannel;
	strncpy(sound->AUDIO_PATH, filepath, FILEPATH_CHAR_LEN);
	return sound;

}

void soundPlay(SoundSys *sound, int numLoops, float volume, int channel, int group) {

	float vol = 1.0f;
	if (!sound) {
		printf("ERROR: Cannot play a NULL sound.\n");
		return;
	}

	if (volume > 0) {
		vol *= volume;
		sound->volume = vol;

	}

	Mix_VolumeChunk(sound->sound, (int)sound->volume);
	Mix_PlayChannel(sound->defaultChannel, sound->sound, numLoops);

}

void play_FileByPath(char *filepath, int numLoops, float volume, int channel, int group) {

	int x = 0;

	for (x = 0; x < soundManager.maxSounds; x++) {
		if (strncmp(soundManager.soundList[x].AUDIO_PATH, filepath, FILEPATH_CHAR_LEN) == 0) {

			soundPlay(&soundManager.soundList[x], numLoops, volume, channel, group);
			return;

		}
	}
	printf("ERROR: Filepath did not provide audio\n", filepath);
	return;

}

void sound_AdjustVolume(SoundSys *sound, float volume) {

	int x = 0;

	for (x = 0; x < soundManager.maxSounds; x++) {
		if (soundManager.soundList[x].inUse > 0) {
			sound_AdjustVolume(&soundManager.soundList[x], volume);
		}
	}
}

void soundFree(SoundSys *sound) {

	if (!sound) {
		printf("ERROR: No audio to free.");
		return;
	}

	sound->inUse = 0;
}

void soundDelete(SoundSys *sound) {

	if (!sound) {
		printf("ERRPR: No audio to delete.\n");
		return;
	}

	if (sound->sound != NULL) {
		Mix_FreeChunk(sound->sound);
	}

	memset(sound, 0, sizeof(SoundSys));

}

void sound_DeleteAll() {

	int x = 0;

	for (x = 0; x < soundManager.maxSounds; x++) {

		soundDelete(&soundManager.soundList[x]);
	}
}
