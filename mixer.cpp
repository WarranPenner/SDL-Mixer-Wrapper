#include "mixer.h"

Mixer::Mixer() {
	if (SDL_Init((SDL_INIT_AUDIO) == 0)) {
		printf("ERROR: SDL_INIT_AUDIO has failed!\n");
		printf("SDL error: %s\n", SDL_GetError());
	}
	
	if (Mix_OpenAudio(FREQUENCY_, MIX_DEFAULT_FORMAT, HARDWARE_CHANNELS_, 
		CHUNK_SIZE_) == -1) {
		printf("ERROR: SDL_Mixer failed to open!\n");
		printf("SDL error: %s\n", Mix_GetError());
	}

	Mix_AllocateChannels(MAX_CHUNKS_PLAYING_);
}

Mixer::~Mixer() {
	Mix_CloseAudio();
	Mix_Quit();
}

Mix_Music* Mixer::loadMusic(std::string path) {
	Mix_Music* m = Mix_LoadMUS(path.c_str());
	if (!m) {
		printf("ERROR: Mix_Music could not be loaded for '%s'!\n",
			path.c_str());
		printf("SDL error: %s\n", Mix_GetError());
	} else {
		return m;
	}
}

void Mixer::playMusic(Mix_Music* m, int volume, int repeats) {
	Mix_VolumeMusic((int)volume);
	if (Mix_PlayMusic(m, repeats) == -1) {
		printf("ERROR: Music file could not be played!\n");
		printf("SDL error: %s\n", Mix_GetError());
	}
}

void Mixer::pauseMusic() {
	Mix_PauseMusic();
}

void Mixer::unpauseMusic() {
	Mix_ResumeMusic();
}

void Mixer::stopMusic() {
	Mix_HaltMusic();
}

void Mixer::fadeMusic(int fadeTime) {
	Mix_FadeOutMusic(fadeTime);
}

void Mixer::changeMusicVolume(int volume) {
	Mix_VolumeMusic((int)volume);
}

Mix_Chunk* Mixer::loadChunk(std::string path) {
	Mix_Chunk* c = Mix_LoadWAV(path.c_str());
	if (!c) {
		printf("ERROR: A Mix_Chunk could not be loaded for '%s'!\n", 
			path.c_str());
		printf("SDL error: %s\n", Mix_GetError());
	} else {
		return c;
	}
}

void Mixer::playChunk(Mix_Chunk* c, int volume, int repeats) {
	Mix_VolumeChunk(c, (int)volume);
	if (Mix_PlayChannel(-1, c, repeats) == -1) {
		if (Mix_GetError() == "No free channels available") {
			printf("WARNING: Mix_Chunk play requests have exceeded the ");
			printf("channels allocated for them!\n");
		} else { 
			printf("WARNING: A Mix_Chunk could not be played!\n");
			printf("SDL error: %s\n", Mix_GetError());
		}
	}
}

void Mixer::pauseChunk(Mix_Chunk* c) {
	int numChannels = Mix_AllocateChannels(-1);

	for (int i = 0; i < numChannels; i++) {
		if (Mix_GetChunk(i) == c) {
			Mix_Pause(i);
		}
	}
}

void Mixer::unpauseChunk(Mix_Chunk* c) {
	int numChannels = Mix_AllocateChannels(-1);

	for (int i = 0; i < numChannels; i++) {
		if (Mix_GetChunk(i) == c) {
			Mix_Resume(i);
		}
	}
}

void Mixer::stopChunk(Mix_Chunk* c) {
	int numChannels = Mix_AllocateChannels(-1);

	for (int i = 0; i < numChannels; i++) {
		if (Mix_GetChunk(i) == c) {
			Mix_HaltChannel(i);
		}
	}
}

bool Mixer::isMusicPlaying() {
	if (Mix_PlayingMusic()) {
		return true;
	} else {
		return false;
	}
}

bool Mixer::isMusicPaused() {
	if (Mix_PausedMusic()) {
		return true;
	} else {
		return false;
	}
}

bool Mixer::isChunkPlaying(Mix_Chunk* c) {
	int numChannels = Mix_AllocateChannels(-1);

	for (int i = 0; i < numChannels; i++) {
		if (Mix_GetChunk(i) == c) {
			if (Mix_Playing(i) && !Mix_Paused(i)) {
				return true;
			}
		}
	}

	return false;
}

bool Mixer::isChunkPaused(Mix_Chunk* c) {
	int numChannels = Mix_AllocateChannels(-1);
	for (int i = 0; i < numChannels; i++) {
		if (Mix_GetChunk(i) == c && Mix_Playing(i) && Mix_Paused(i)) {
			return true;
		}
	}

	return false;
}