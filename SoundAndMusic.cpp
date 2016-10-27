#include "SoundAndMusic.h"
#include "SDL_mixer.h"

// Fredik Zaar SP6 Demon Hunter

Control_Sound_And_Music Sound_Music;

Control_Sound_And_Music::Control_Sound_And_Music()
{

	Mix_Music *music = NULL;
	Mix_Music *musicMenu = NULL;
	Mix_Music *musicOutro = NULL;
	
	Mix_Chunk *Fireball = NULL; 
	Mix_Chunk *Hit = NULL; 
	Mix_Chunk *Punch = NULL; 
	Mix_Chunk *Dontknow = NULL; 
	Mix_Chunk *Morph = NULL;
	Mix_Chunk *Boss = NULL;
	Mix_Chunk *FireBall_Explode = NULL;

	MusicOn = false;
	MusicPaused = false;

	bool check = false;
	LevelSong = false;
	MenuSong = false;
	BossEffect = false;
	OutroSong = false;

	check = Load_Files();
}

void Control_Sound_And_Music::PlayMusic( int song )
{
	if( song == MUSIC_START )
	{
		Mix_PlayMusic( music, -1 );
		LevelSong = true;
		MenuSong = false;
		OutroSong = false;
	
	}
	else if( song == MUSIC_MENU )
	{
		Mix_PlayMusic( musicMenu, -1 );
		MenuSong = true;
		LevelSong = false;
		OutroSong = false;
	}
	else if( song == MUSIC_OUTRO )
	{
		Mix_PlayMusic( musicOutro, -1 );
		MenuSong = false;
		LevelSong = false;
		OutroSong = true;
	}

}
void Control_Sound_And_Music::PlaySoundEffect( int effect )
{
	if( effect == SOUND_MORPH )
	{
			Mix_PlayChannel( -1, Morph, 0 );
	}
	else if( effect == SOUND_HIT )
	{
			Mix_PlayChannel( -1, Punch, 0 );
	}
	else if( effect == SOUND_FIRE )
	{
			Mix_PlayChannel( -1, Fireball, 0 );
	}
	else if( effect == SOUND_GETS_HIT )
	{
			Mix_PlayChannel( -1, Hit, 0 );
	}
	else if( effect == SOUND_DIE )
	{
			Mix_PlayChannel( -1, Dontknow, 0 );
	}
	else if( effect == SOUND_BOSS )
	{
			Mix_PlayChannel( -1, Boss, 0 );
	}
	else if( effect == SOUND_FIREBALL_EXPLODE )
	{
		Mix_PlayChannel( -1, FireBall_Explode, 0 );
	}
}

void Control_Sound_And_Music::PlayIntroSong()
{
	if( LevelSong == true )
	{
		PauseMusic();
	}
	if( MenuSong == false )
	{
		PlayMusic( 1 );
	}
}
void Control_Sound_And_Music::PlayLevelSong()
{

}

bool Control_Sound_And_Music::Load_Files()
{

	if( Mix_OpenAudio( 22500, MIX_DEFAULT_FORMAT, 2, 800 ) == -1 ) 
	{ 
		return false; 
	} 

	//Load the music 
	music = Mix_LoadMUS( "Music/End.wav" ); 
	musicMenu = Mix_LoadMUS( "Music/menuSong.wav" );
	musicOutro = Mix_LoadMUS( "Music/Outro.wav" );

	// load all sound
	Morph = Mix_LoadWAV( "Music/Wolf.wav" );
	Hit = Mix_LoadWAV( "Music/Hit.wav" );
	Punch = Mix_LoadWAV( "Music/Hits.wav" );
	Dontknow =  Mix_LoadWAV( "Music/haha.wav" );
	Boss = Mix_LoadWAV( "Music/Doom.wav" );
	Fireball = Mix_LoadWAV( "Music/FireBall.wav" );
	FireBall_Explode = Mix_LoadWAV( "Music/FireballExplode.wav" );
	
	//If there was a problem loading the sound effects 
	if( ( Fireball == NULL ) || ( Hit == NULL ) || 
		( Punch == NULL ) || ( Dontknow == NULL ) || 
		( Boss == NULL ) || ( Morph == NULL ) ||
		( FireBall_Explode == NULL ) ) 
	{ 
		return false; 
	} 
	
	//If everything loaded fine 
	return true; 


}

void Control_Sound_And_Music::PauseMusic()
{
	Mix_PauseMusic();
	MusicPaused = true;
}

void Control_Sound_And_Music::UnpauseMusic()
{
	if( Mix_PausedMusic() == 1 )
	{
		Mix_ResumeMusic();
		MusicPaused = false;
	}
}
