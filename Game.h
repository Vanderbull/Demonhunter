#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <sstream>
#include <windows.h>
#include "Paralaxlayers.h"
#include <iostream>
#include "Objects.h"
#include "SDL_mixer.h"
#include "characters.h"
#include <list>
#include "Enemies.h"
#include <fstream>
#include "Intro.h"
#include "Start.h"
#include "Collision.h"
#include "OutroFinish.h"
#include "GetInput.h"
#include "HighScore.h"

enum{	GS_INTRO, GS_LEVEL1, GS_LEVEL1BOSS, GS_OUTRO, 
		GS_LOADING, GS_INTROSTORY, GS_MORPH, GS_DEAD, GS_ENTERNAME };
enum{ BOSS_IDLE, BOSS_ATTACK, BOSS_DIE };
enum{ HEAD_GO, HEAD_DOWN, HEAD_CRASH };

const int MAX_SURFACE = 128;
const int ANIMPACE = 150;
const int ANIMPACESLOWER = 300;
const int ANIMPACEENEMY = 50;
const int ANIMPACEBOSSHEAD = 5;

const int DEMONHEIGHT = 100;
const int DEMONWIDTH = 130;
const int DEMONWIDTHREAL = 25;
const int DEMONHEIGHTREAL = 25;

const int GROUND_Y = 450;
const int GROUND_X = 400;
const int STARTSCROLLING = 600;
const int BOSS_ATTACK_START = 150;

using namespace std;

class Gamestate
{
public:
	Gamestate();
	
	ParallaxBackground *Paralax;

	int SCREEN_HEIGHT, SCREEN_WIDTH;
	int SCREEN_BPP;

	int Current_AnimArray, Previous_AnimArray;
	int Current_Frame, Previous_Frame;
	
	int GameCondition;
	int m_paralax;
	int WhichMorphType();
	int Score;

	int findAvailableIndex();
	int Load_imageAlpha( std::string filename, int r, int g, int b );

	float dt;
	float ScreenSize;
	float UpDateAnimationSpeed;

	bool GameOK;
	bool FirstLevel, SecondLevel, ThirdLevel;
	bool OK_Pace();
	bool OK_PaceEnemy();

	bool BossStart;
	bool Skeleton_Attack;
	bool IntroDone;
	bool CheckingHighScore;
	bool Weather;

	char text_out[ 256 ];
	string ScoreString;

	SDL_Surface * screen;
	SDL_Surface * BackBuffer;

	void CreateAll();
	void resetAnimationPace();
	void AddTick();
	void blit( int index, int xpos, int ypos, bool transparent );
	void drawParallaxLayers();

	void RecordAllData();
	void Loading();
	void DrawAllText();
	void DoIntroTalk();
	void MorphMyDude();
	void EndAll();
	
	void MainScreen();
	void EnterName();
	void DrawSprite();
	void DrawObjects();
	void DrawBoss();
	void DrawBackgroundBlack();
	void CreateNewThings();
	void setUpParallaxLayers();
	void load_files();

	void FLIP();
	SDL_Surface * GetSurface( int WhichSurface );

	void stretchBlit( ParallaxLayer * layer, SDL_Rect srcRect, SDL_Rect destRect );
	void PasteScreenToAnother( SDL_Rect srcRect, SDL_Rect destRect );
	void stretchPicToBackBuffer( ParallaxLayer * layer, SDL_Rect srcRect, SDL_Rect destRect  );
	void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL );

	void PlayerDied();
	void RestartGame();
	void ResetBoss();
	void ResetEnemies();
	void ResetObjects();
	void ResetPlayer();
	void ResetRest();
	void PlayOutro();

	string HighScoreList[ 6 ];

	Boss * CreateBoss( int xPos, int yPos, int surface );

	SDL_Rect MorphingPics[ 5 ];

	TTF_Font * font;

	Boss * boss;
	IntroTalk * Intro;
	Outro * outro;
	StringInput * name;
	FillHighScore * ListHighScore;
	DancingDragon * Dragon;
	FirstScreen * TitleScreen;

	

	int m_srfGrass, m_srfBack, m_srfFence, m_srfClouds, m_srfTree, m_srfEnemyZombie,
		m_srfSkeleton, m_srfCrow, m_srfCoffin, m_srfTrees, m_srfBlack, m_srfBoss, 
		m_srfDemonLife, m_srfDemonHealthAndFire, m_srfDragon, m_srfStart, m_srfButtons,
		m_srfIntro, m_srfPower, m_srfMorphing, m_srfReaper, m_srfOutro;

	SDL_Surface * text;
	SDL_Surface * textIntro;
	SDL_Surface * DeathSurface[ 2 ];
	SDL_Surface * TypeName;
	
private:
	SDL_Surface * m_surfaceList[ MAX_SURFACE ];
	
};

extern Gamestate gamestate;

class Game
{
public:
	Game();
	void upDate( SDL_Event input );
	bool Init( SDL_Surface * &screen );
	void Handle_events( SDL_Event input );
	void cleanUp();

private:

};

