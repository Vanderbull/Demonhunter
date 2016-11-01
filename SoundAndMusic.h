#pragma once
#include "SDL_mixer.h"

enum{	MUSIC_START, MUSIC_MENU, MUSIC_OUTRO, SOUND_MORPH, SOUND_HIT, SOUND_FIRE, 
		SOUND_GETS_HIT, SOUND_DIE, SOUND_BOSS, SOUND_FIREBALL_EXPLODE };

class Control_Sound_And_Music
{
public:
	Control_Sound_And_Music();

	bool Load_Files();

	Mix_Music *music; 
	Mix_Music *musicMenu;
	Mix_Music *musicOutro;
	
	Mix_Chunk *Fireball; 
	Mix_Chunk *Hit; 
	Mix_Chunk *Punch; 
	Mix_Chunk *Dontknow; 
	Mix_Chunk *Morph;
	Mix_Chunk * Boss;
	Mix_Chunk *FireBall_Explode;

	bool MusicOn;
	bool MusicPaused;
	bool BossEffect;

	bool LevelSong, MenuSong, OutroSong;

	void PlayMusic( int song );
	void PlaySoundEffect( int effect );
	void PauseMusic();
	void UnpauseMusic();
	void PlayIntroSong();
	void PlayLevelSong();
};

extern Control_Sound_And_Music Sound_Music;
