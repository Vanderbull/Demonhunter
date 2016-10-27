#pragma once

#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "Game.h"
#include "characters.h"
#include <windows.h>
#include <sstream>
#include <stdlib.h>
#include <fstream>
#include <cmath>
#include "Objects.h"
#include "Enemies.h"
#include "TImers.h"
#include "Paralaxlayers.h"
#include "Animals.h"
#include "Start.h"

Gamestate gamestate;

Gamestate::Gamestate()
{

	SCREEN_HEIGHT = 600;
	SCREEN_WIDTH = 800;
	SCREEN_BPP = 32;

	dt = 0.0;
	FirstLevel = true;
	BossStart = false;
	Skeleton_Attack = false;
	IntroDone = false;
	ScreenSize = 0;
	GameCondition = GS_INTRO;

	Previous_AnimArray = 0;
	Previous_Frame = 0;
	Current_AnimArray = 0;
	Current_Frame = 0;

	

	m_paralax = 0;
	Score = 0;

}

Tree * Gamestate::CreateTree( int xPos, int yPos )
{
	Tree * temp = new Tree;
	temp->xPos = xPos;
	temp->yPos = yPos;

	return temp;

}

void Game::Handle_events( SDL_Event input )
{	
	
	
	// checks input for keypresses and releases
	if( input.type == SDL_KEYUP )
	{
		switch( input.key.keysym.sym )
		{
		case SDLK_RIGHT:
			{
				demon.isMovingRight = false;
				break;
			}
		case SDLK_LEFT:
			{
				demon.isMovingLeft = false;
				break;
			}
		case SDLK_UP:
			{
				demon.isJumping = false;
				break;
			}
		case SDLK_DOWN:
			{
				demon.isCrouching = false;
				break;
			}
		case SDLK_SPACE:
			{
				demon.isKicking = false;
				break;
			}
		case SDLK_LALT:
			{
				if( demon.SmallHunter )
				{
					demon.isPunching = false;
				}
				break;
			}
		}
	}
	else if( input.type == SDL_KEYDOWN )
	{
		switch( input.key.keysym.sym )
		{
		case SDLK_RIGHT:
			{
				if( demon.isCrouching == false && demon.isKicking == false 
					&& demon.isPunching == false && demon.isJumping == false && demon.yPos == GROUND_Y )
				{	
					demon.isMovingRight = true;
				}
				break;
			}
		case SDLK_LEFT:
			{
				if( demon.isCrouching == false && demon.isKicking == false 
					&& demon.isPunching == false && demon.isJumping == false && demon.yPos == GROUND_Y )
				{
					demon.isMovingLeft = true;
				}
				break;
			}
		case SDLK_UP:
			{
				if( demon.isCrouching == false && demon.isPunching == false 
					&& demon.isKicking == false && demon.isJumping == false 
					&& demon.yPos == GROUND_Y )
				{
					demon.isJumping = true;
				}
				break;
			}
		case SDLK_DOWN:
			{
				if( demon.isJumping == false && demon.isKicking == false && demon.isPunching == false 
					&& demon.isMovingLeft == false && demon.isMovingRight == false )
				{
					demon.isCrouching = true;
				}
				break;
			}
		case SDLK_SPACE:
			{
				if( gamestate.GameCondition == 0 )
				{
					gamestate.IntroDone = true;
				}

				if( demon.isPunching == false  
				 && demon.isKicking == false && demon.isJumping == false )
				{
					demon.isKicking = true;
				}
				break;
			}
		case SDLK_LALT:
			{
				if( demon.isPunching == false 
				 && demon.isKicking == false && demon.isJumping == false )
				{
				demon.isPunching = true;
				}
				break;
			}
		}
	}

	else
	{
		return;
	}
	
}

bool Gamestate::CheckCollisionWithPlayer( Enemy *MyEnemy, int WhichCollisionToUse )
{
	
	bool temp = false;

	if( MyEnemy->Die == true )
	{
		return false;
	}

	if( WhichCollisionToUse == 1 )
	{
		temp = CollisionCircle( &demon, MyEnemy );
	}

	return temp;
}

// ----------------------------------------------------------------------------
// circleCollision - test if circles overlap
// ----------------------------------------------------------------------------

bool Gamestate::CollisionCircle( Demon *MyDemon, Enemy *MyEnemy )
{

	// Cache
	double	dx = ( ( MyDemon->xPos + DEMONWIDTHREAL / 2 ) - ( MyEnemy->xPos + MyEnemy->Enemy_Width / 2 ) ),
			dy = ( ( MyDemon->yPos + DEMONHEIGHTREAL / 2 ) - ( MyEnemy->yPos + MyEnemy->Enemy_Height / 2 ) );

	int dist = (int)sqrt( dx*dx + dy*dy );

	// Do circles overlap?
	if( dist < MyDemon->Radius + MyEnemy->radius )
	{
		return true;	// Yep, collision
	}

	// No collision
	return false;
}

Game::Game()
{
	gamestate.GameOK = true;
	gamestate.GameOK = Init( gamestate.screen );
	
	demon.InitiateDemon( demon.DemonSurface, GROUND_X, GROUND_Y, DEMONHEIGHT, DEMONWIDTH ); 

	gamestate.load_files();
	demon.Set_clips();
}

void Gamestate::load_files()
{	
	m_srfGrass = Load_imageAlpha( "Graphics\\nyabananstor.png", 0, 0, 0 );
	m_srfFence = Load_imageAlpha( "Graphics\\Fence.png", 0, 0, 0 );
	m_srfClouds = Load_imageAlpha( "Graphics\\cloud.png", 0, 0, 0 );
	m_srfBlack = Load_imageAlpha( "Graphics\\firstlayer.png", 0, 0, 0 );
	m_srfBack = Load_imageAlpha( "Graphics\\sky.png", 0, 0, 0 );
	// har rgb 2, 2, 2 skicka med kolla sdk i morgon
	m_srfTrees = Load_imageAlpha( "Graphics\\trees.png", 2, 2, 2 );
	demon.DemonSurface = Load_imageAlpha( "helagubben.png", 255, 255, 255 );
	m_srfEnemyZombie = Load_imageBrownAlpha( "Graphics\\Zombie.png" );
	m_srfSkeleton = Load_imageBrownAlpha( "skelettSpritesheet.png" );
	m_srfCrow = Load_imageAlpha( "crow.png", 255, 255, 255 );
	m_srfCoffin  = Load_imageBrownAlpha( "SpriteSheetCoffin.png" );
	m_srfBoss = Load_imageAlpha( "bosssheet.png", 255, 255, 255 );
	m_srfDemonLife = Load_imageAlpha( "olikasakervittalpha", 255, 255, 255 );
	m_srfDemonHealthAndFire = Load_imageAlpha( "olikasakersvartalpha", 0, 0, 0 );
	m_srfDragon = Load_imageAlpha( "DragonSprite.png", 0, 0, 0 );
	m_srfStart = Load_imageAlpha( "Graphics\\start.png", 237, 234, 214 );
	m_srfButtons = Load_imageAlpha( "Graphics\\buttons.png", 255, 0, 0 );

	Dragon = new DancingDragon( m_srfDragon );
	TitleScreen = new FirstScreen(	0, 0, 800, 600, 50, 550, 150, 550, 185, 185, 250, 
						550, gamestate.m_srfStart, gamestate.m_srfButtons );
	//sets up my background layers
	setUpParallaxLayers();
}

// ----------------------------------------------------------------------------
// findAvailableIndex() - find free slot in surface list and return its index
// ----------------------------------------------------------------------------
int Gamestate::findAvailableIndex()
{
	for( int i = 0; i < MAX_SURFACE; i++ )
	{
		if( !m_surfaceList[i] )
		{
			return i;
		}
	}

	// None available
	return -1;
}

void Gamestate::DrawObjects()
{
	Control_ENEMY.Draw_Enemies();
	Control_Anim.Draw_Animals();
	Control_OBJ.DrawObjects();
	
}

Boss * Gamestate::CreateBoss( int xPos, int yPos, int surface )
{
	Boss * temp = new Boss;
	temp->surface = surface;
	temp->xPos = xPos;
	temp->yPos = yPos;

	temp->radius = ( temp->Width > temp->Height ) ? temp->Width / 2 : temp->Height  / 2;

	return temp;
}

void Game::upDate( SDL_Event input )
{

	if( demon.WhereIsEnd >= 500 )
	{
		gamestate.GameCondition = GS_LEVEL1BOSS;
		demon.WhereIsEnd = 0;
	}

		// Check game state
	switch( gamestate.GameCondition )
	{

		// Intro sequence
		case GS_INTRO:
			{
				
				gamestate.MainScreen();
				break;
			}
		case GS_LOADING:
			{
				Handle_events( input );
				gamestate.Loading();
			}

		// Level1 Loop
		case GS_LEVEL1:
			{
			
				// handles events what the user does with the character
				Handle_events( input );

				//draws layers
				gamestate.drawParallaxLayers();
				gamestate.DrawObjects();
				gamestate.DrawSprite();
				gamestate.FLIP();
				break;
			
			}
		case GS_LEVEL1BOSS:
			{
				// handles events what the user does with the character
				Handle_events( input );

				//draws layers
				gamestate.drawParallaxLayers();
				gamestate.DrawBoss();
				gamestate.DrawSprite();
				gamestate.FLIP();
				break;
			}

		case GS_OUTRO:
			{
				break;
			}
	}
	
}

void Gamestate::Loading()
{
	ParallaxLayer  * MyParaBackGround;
	MyParaBackGround = Paralax->getLayer( 0 );

	SDL_Rect scRect = { 0, 0,	MyParaBackGround->m_width, 
								MyParaBackGround->m_height };

	SDL_Rect dtRect = {	0, 0, MyParaBackGround->DW, MyParaBackGround->DH };

	SDL_BlitSurface( m_surfaceList[ MyParaBackGround->m_surface ], &scRect, gamestate.screen, &dtRect ); 

	SDL_Rect dstRect = { Dragon->xPos, Dragon->yPos, Dragon->Width, Dragon->Height };
	if ( gamestate.IntroDone == false )
	{
		if( Dragon->StateCounter > 2 )
		{
			SDL_BlitSurface(	m_surfaceList[ Dragon->surface ], &Dragon->Clips[ Dragon->Frame ],
								gamestate.screen, &dstRect );
			Dragon->PrevFrame = Dragon->Frame;
			Dragon->SetFrame();
			Dragon->StateCounter = 0;
		}
		else
		{
				SDL_BlitSurface(	m_surfaceList[ Dragon->surface ], &Dragon->Clips[ Dragon->PrevFrame ],
									gamestate.screen, &dstRect );
				Dragon->StateCounter++;	
		}
	
		
	}
	else
	{

		delete Dragon;

		gamestate.GameCondition = GS_LEVEL1;

	}

	gamestate.FLIP();
}

void Gamestate::DrawBoss()
{
	gamestate.boss->UpdateBoss();
}

SDL_Surface * Gamestate::GetSurface( int WhichSurface )
{
	return m_surfaceList[ WhichSurface ];	
}

void Gamestate::FLIP()
{
	SDL_Rect srcRect = { 0, 0, gamestate.BackBuffer->w, gamestate.BackBuffer->h };
	SDL_Rect destRect = {	0, 0, gamestate.SCREEN_WIDTH, gamestate.SCREEN_HEIGHT };
					
	gamestate.PasteScreenToAnother( srcRect, destRect );

	//flips screen
	if( SDL_Flip( gamestate.screen ) == -1)
	{
		gamestate.GameOK = false;
	}
}

// ----------------------------------------------------------------------------
// doCoolIntro() - the hero makes his entrance!
// ----------------------------------------------------------------------------
void Gamestate::MainScreen()
{
	int IntroState = 0;
	int StateCounter = 0;
	bool Clear = false;

	ParallaxLayer  * MyParaBackGround;
	MyParaBackGround = Paralax->getLayer( TitleScreen->surface );

	SDL_Rect scRect = { 0, 0,	TitleScreen->Width, 
								TitleScreen->Height };

	SDL_Rect dtRect = {	0, 0, TitleScreen->Width, TitleScreen->Height };

	SDL_BlitSurface( gamestate.GetSurface( TitleScreen->surface ), &scRect, gamestate.BackBuffer, &dtRect ); 

	bool ButtonNew = false;
	bool ButtonOp = false;
	bool ButtonQuit = false;

	for( int i = 0; i < 3; i++ )
	{
		SDL_Rect dstRect = { TitleScreen->ButtonClips[ i ].x, TitleScreen->ButtonClips[ i ].y , TitleScreen->Button_Width, TitleScreen->Button_Height };
		SDL_BlitSurface( gamestate.GetSurface( TitleScreen->SurfaceButt ), &TitleScreen->ButtonClips[ i ],
						 gamestate.BackBuffer, &dstRect ); 
	}
	
	//gamestate.GameCondition = GS_LEVEL1;
	
	if( Clear == false )
	{

		if( ButtonNew == true )
		{
			gamestate.GameCondition = GS_LEVEL1;
		}

		if( ButtonOp == true )
		{
			// set Gamestate options
			return;
		}

		if( ButtonQuit == true )
		{
			//set gamestate Quit
			return;
		}
		

	}

	//// Check which part of the intro we are in....
	//switch( introState )
	//{
	//	// Wait a bit....
	//	case 0:
	//		{
	//			stateCounter++;
	//			if( stateCounter > 500 || ( SDLK_SPACE ) )
	//			{
	//				introState = 1;
	//				stateCounter = 0;
	//			}
	//			break;
	//		}

	//	// Hero comes crashing down...
	//	case 1:
	//		{
	//			demon.yPos += 10.0f;	// move player downwards...

	//			// Hit ground?
	//			if( demon.yPos > GROUND_Y - 10.0f )
	//			{
	//				demon.yPos = GROUND_Y;
	//				gamestate.GameCondition= GS_LEVEL1;	// All done! Intro is over and
	//											// game begins...
	//			}

	//			break;
	//		}

	//	// Should never get here...
	//	default:
	//		break;
	//}

	
			
	//	
	//// Draw background
	//gamestate.drawParallaxLayers();
	//gamestate.DrawSprite();
	
	// Print information
	//if( introState == 0 )
	//{
	//	int x = 0;
	//}



	// Show result
	gamestate.FLIP();
}

void Game::cleanUp()
{
	
	SDL_Quit();
}

void Gamestate::RecordAllData()
{
	ParallaxLayer * LayerToFile;
	ofstream OutToFile("LevelOptions.txt");
	for( int i = 0; i < Paralax->getLayerCount(); i++ )
	{
		LayerToFile = Paralax->getLayer( i );
		OutToFile << "WhichLayer: " << i << endl;
		OutToFile << "Layer_Surface: " << LayerToFile->m_surface << endl;
		OutToFile << "Layer_Width: " << LayerToFile->m_width << endl;
		OutToFile << "Layer_Height: " << LayerToFile->m_height << endl;
		OutToFile << "Layer_WhereOn_Y: " << LayerToFile->m_surfaceYOffset << endl;
		OutToFile << "Layer_Parallax: " << LayerToFile->m_parallax << endl;
		OutToFile << "Destination_X: " << LayerToFile->DX << endl;
		OutToFile << "Destination_Y: " << LayerToFile->DY << endl;
		OutToFile << "Destination_Width: " << LayerToFile->DW << endl;
		OutToFile << "Destination_Height: " << LayerToFile->DH << endl;
		OutToFile << endl;
	}
}

SDL_Surface * Gamestate::Load_imageToSurface(std::string filename)
{
	//temp storage for the image loaded
	SDL_Surface * loadedimage = NULL;

	//optimized image for storage and flipping
	SDL_Surface * optimizedImage = NULL;

	//load image 
	loadedimage = IMG_Load( filename.c_str() );

	//if something went wrong
	if( loadedimage != NULL )
	{
		//create an optimized image 
		optimizedImage = SDL_DisplayFormat( loadedimage );

		//free old image
		SDL_FreeSurface( loadedimage );
	}

	if(optimizedImage != NULL)
	{
		SDL_SetColorKey(optimizedImage, SDL_RLEACCEL | SDL_SRCCOLORKEY, SDL_MapRGB(optimizedImage->format, 0, 0xFF, 0xFF));
	}
	
	return optimizedImage;
}

//loads image with black colorkeying
int Gamestate::Load_imageBrownAlpha(std::string filename)
{
	//temp storage for the image loaded
	SDL_Surface * loadedimage = NULL;

	//optimized image for storage and flipping
	SDL_Surface * optimizedImage = NULL;

	//load image 
	loadedimage = IMG_Load( filename.c_str() );

	//if something went wrong
	if( loadedimage != NULL )
	{
		//create an optimized image 
		optimizedImage = SDL_DisplayFormat( loadedimage );

		//free old image
		SDL_FreeSurface( loadedimage );
	}

	if(optimizedImage != NULL)
	{
		SDL_SetColorKey(optimizedImage, SDL_RLEACCEL | SDL_SRCCOLORKEY, SDL_MapRGB(optimizedImage->format, 106, 76, 48 ) );
	}
	
	int index = findAvailableIndex();
	if( index == -1 )
	{
		return -1;
	}

	m_surfaceList[ index ] = optimizedImage;
	return index;
}

int Gamestate::Load_imageAlpha( std::string filename, int r, int g, int b )
{
	//temp storage for the image loaded
	SDL_Surface * loadedimage = NULL;

	//optimized image for storage and flipping
	SDL_Surface * optimizedImage = NULL;

	//load image 
	loadedimage = IMG_Load( filename.c_str() );

	//if something went wrong
	if( loadedimage != NULL )
	{
		//create an optimized image 
		optimizedImage = SDL_DisplayFormat( loadedimage );

		//free old image
		SDL_FreeSurface( loadedimage );
	}

	if(optimizedImage != NULL)
	{
		SDL_SetColorKey(optimizedImage, SDL_RLEACCEL | SDL_SRCCOLORKEY, SDL_MapRGB(optimizedImage->format, r, g, b ) );
	}
	
	int index = findAvailableIndex();
	if( index == -1 )
	{
		return -1;
	}

	m_surfaceList[ index ] = optimizedImage;
	return index;
}

bool Game::Init(SDL_Surface * &screen)
{

	gamestate.screen = 0;
	//initialize all SDL subystems
	if( SDL_Init( SDL_INIT_EVERYTHING ) == -1)
	{
		return false;
	}

	//set up the screen
	gamestate.screen = SDL_SetVideoMode(gamestate.SCREEN_WIDTH, gamestate.SCREEN_HEIGHT, gamestate.SCREEN_BPP, SDL_SWSURFACE );

	if( screen == NULL )
	{
		return false;
	}

	//set window caption
	SDL_WM_SetCaption( " Demon hunter ", NULL);
	
	    /* Create a 32-bit surface with the bytes of each pixel in R,G,B,A order,
       as expected by OpenGL for textures */
    Uint32 rmask, gmask, bmask, amask;

	/* SDL interprets each pixel as a 32-bit number, so our masks must depend
	   on the endianness (byte order) of the machine */

	rmask = 0x00000000;
	gmask = 0x00000000;
	bmask = 0x00000000;
	amask = 0x00000000;

	gamestate.BackBuffer = SDL_CreateRGBSurface( SDL_SWSURFACE, 800, 600, 32,
								   rmask, gmask, bmask, amask);
	if( gamestate.BackBuffer == NULL )
	{
		return false;
	}

	return true;

}

// ----------------------------------------------------------------------------
// drawParallaxLayers() - renders parallax-layers to backbuffer and gives it to Main Surface
// ----------------------------------------------------------------------------
void Gamestate::drawParallaxLayers()
{
	if( gamestate.GameCondition != GS_LEVEL1BOSS )
	{
		if( demon.xVel >= SCREEN_WIDTH - 350 )
		{
			if( demon.isMovingRight )
			{
				gamestate.m_paralax += 2;
			}
			else if( demon.isMovingLeft )
			{
				gamestate.m_paralax -= 2;
			}
		}

		gamestate.CreateAll();
	}
	else
	{
		if( BossStart == false )
		{
			demon.DemonHunter = true;
			demon.SmallHunter = false;
			gamestate.boss = gamestate.CreateBoss( SCREEN_WIDTH -200, GROUND_Y-210, m_srfBoss );
			BossStart = true;
		}
	}

		//// Draw parallax layers
		ParallaxLayer  * MyParaBackGround;
		MyParaBackGround = Paralax->getLayer( 0 );

		SDL_Rect scRect = { 0, 0,	MyParaBackGround->m_width, 
									MyParaBackGround->m_height };

		SDL_Rect dtRect = {	0, 0, MyParaBackGround->DW, MyParaBackGround->DH };

		SDL_BlitSurface( m_surfaceList[ MyParaBackGround->m_surface ], &scRect, gamestate.BackBuffer, &dtRect ); 

		//gamestate.stretchPicToBackBuffer( MyParaBackGround, scRect, dtRect );

		int x = 0;
		for( int i = 1; i < Paralax->getLayerCount(); ++i )
		{		
			// Calc rects
			MyParaBackGround = Paralax->getLayer( i );
			if( MyParaBackGround->m_surface == m_srfClouds )
			{
				MyParaBackGround->AnimClouds++;

				//////// Calc parallax position
				x = (int)( MyParaBackGround->m_parallax * (float)( +MyParaBackGround->AnimClouds ) );  
				if( x < 0 )	// neg -> pos
				{
					x *= -1;	// invert sign, because % only works with positive integers
					x = MyParaBackGround->m_width - (x % MyParaBackGround->m_width);
				}
				else
				{
					x %= MyParaBackGround->m_width;
				}

				x -= MyParaBackGround->m_width;	// move one back
			}
			else
			{

				//////// Calc parallax position
				x = (int)( MyParaBackGround->m_parallax * (float)( +gamestate.m_paralax ) );  
				if( x < 0 )	// neg -> pos
				{
					x *= -1;	// invert sign, because % only works with positive integers
					x = MyParaBackGround->m_width - (x % MyParaBackGround->m_width);
				}
				else
				{
					x %= MyParaBackGround->m_width;
				}

				x -= MyParaBackGround->m_width;	// move one back
			}

			for( int i = 0; i < 2; i++ )
			{
				SDL_Rect sourceRect = { 0 + x, MyParaBackGround->m_surfaceYOffset,
										MyParaBackGround->m_width, MyParaBackGround->m_height };

				SDL_Rect destinationRect = {	MyParaBackGround->DX, MyParaBackGround->DY, 
												MyParaBackGround->DW, MyParaBackGround->DH };
			
				SDL_BlitSurface( m_surfaceList[ MyParaBackGround->m_surface ], &sourceRect, gamestate.BackBuffer, &destinationRect ); 
				
				
				x += MyParaBackGround->m_width;
			}


			MyParaBackGround->HowFarGone = MyParaBackGround->Xpos - MyParaBackGround->m_width;

		}

		/*demon.xPos -= x;*/

		
}

void Gamestate::CreateAll()
{
	Control_ENEMY.Create_Enemies();
	Control_Anim.Create_Animals();
}

void Gamestate::DrawSprite()
{
		SDL_Rect demonDest = { demon.xPos, demon.yPos, demon.Demon_Width, demon.Demon_Height };

		if( gamestate.OK_Pace() )
		{
			Current_AnimArray = gamestate.WhichMorphType();
			Current_Frame = demon.UpdatePlayer();
		
			SDL_BlitSurface(	m_surfaceList[ demon.DemonSurface ], 
								&demon.AnimationArrays[ Current_AnimArray ][ Current_Frame ],
								gamestate.screen, &demonDest );

			gamestate.resetAnimationPace();
			Previous_AnimArray = Current_AnimArray;
			Previous_Frame = Current_Frame;
		}
		else
		{
			SDL_BlitSurface(	m_surfaceList[ demon.DemonSurface ], 
								&demon.AnimationArrays[ Previous_AnimArray ][ Previous_Frame ],
								gamestate.screen, &demonDest );
			demon.UpdateXPos();
		}

}

int Gamestate::WhichMorphType()
{
	if( demon.SmallHunter )
	{
		return 0;
	}

	else if( demon.MediumHunter )
	{
		return 1;
	}

	else if( demon.LargeHunter )
	{
		return 2;
	}

	else if( demon.DemonHunter )
	{
		return 3;
	}

	return 0;
}

bool Gamestate::OK_Pace()
{
	if( UpDateAnimationSpeed > ANIMPACE )
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool Gamestate::OK_PaceEnemy()
{
	if( UpDateAnimationSpeed > ANIMPACEENEMY )
	{
		return true;
	}
	return false;
}

void Gamestate::AddTick()
{
	 float Speed = 1000.0f * ( gamestate.dt / 1000 );;
	 UpDateAnimationSpeed += Speed;
}

void Gamestate::resetAnimationPace()
{
	UpDateAnimationSpeed = 0;
}

void Gamestate::apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip )
{
    //Holds offsets
    SDL_Rect offset;
    
    //Get offsets
    offset.x = x;
    offset.y = y;
    
    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}

void Gamestate::stretchPicToBackBuffer( ParallaxLayer * layer, SDL_Rect srcRect, SDL_Rect destRect )	
{			

	int srcWidth = srcRect.w - srcRect.x;
	int srcHeight = srcRect.h - srcRect.y,
		DestWidth = destRect.w - destRect.x,
		DestHeight = destRect.h - destRect.y;

	SDL_LockSurface( gamestate.BackBuffer );
	SDL_LockSurface( m_surfaceList[ layer->m_surface ] );

	int dstPitch = gamestate.BackBuffer->pitch;
	int pitch = m_surfaceList[ layer->m_surface ]->pitch;

	DWORD * dst = ( DWORD * )gamestate.BackBuffer->pixels;

	DWORD * src = ( DWORD * )m_surfaceList[ layer->m_surface ]->pixels;

	float scaleWidth = srcWidth / ( float )DestWidth;
	float scaleHeight = srcHeight / ( float )DestHeight; 


	float fSrcX = srcRect.x,
		  fSrcY = srcRect.y;

	for(int y = destRect.y;  y < destRect.y + destRect.h; y++ )
	{
		fSrcX = 0;

		for(int x = destRect.x ;  x < destRect.x + destRect.w ; x++)
		{
			dst[ ( y * dstPitch / 4) + ( x ) ] = src[ int( ( fSrcY ) * ( pitch / 4 ) + int( fSrcX ) )];

			fSrcX += scaleWidth;
		}

		fSrcY += scaleHeight;	
	}

	SDL_UnlockSurface( gamestate.BackBuffer );
	SDL_UnlockSurface( m_surfaceList[ layer->m_surface ] );

}

void Gamestate::stretchBlit( ParallaxLayer * layer, SDL_Rect srcRect, SDL_Rect destRect )	
{			

	SDL_LockSurface( gamestate.BackBuffer );
	SDL_LockSurface( m_surfaceList[ layer->m_surface ] );

	int dstPitch = gamestate.BackBuffer->pitch;
	int pitch = m_surfaceList[ layer->m_surface ]->pitch;

	DWORD * dst = ( DWORD * )gamestate.BackBuffer->pixels;

	DWORD * src = ( DWORD * )m_surfaceList[ layer->m_surface ]->pixels;

	float scaleWidth = srcRect.w / ( float )destRect.w;
	float scaleHeight = srcRect.h / ( float )destRect.h; 


	float fSrcX = srcRect.x,
		  fSrcY = srcRect.y;

	for(int y = destRect.y;  y < destRect.y + destRect.h; y++ )
	{
		fSrcX = srcRect.x;

		for(int x = destRect.x ;  x < destRect.x + destRect.w ; x++)
		{
			dst[ (y * dstPitch / 4) + (x) ] = src[ int((fSrcY) * (pitch / 4) + int(fSrcX) )];

			fSrcX += scaleWidth;
		}
		fSrcY += scaleHeight;	
	}

	SDL_UnlockSurface( gamestate.BackBuffer );
	SDL_UnlockSurface( m_surfaceList[ layer->m_surface ] );

}

void Gamestate::PasteScreenToAnother( SDL_Rect srcRect, SDL_Rect destRect )	
{			

	SDL_LockSurface( gamestate.screen );
	SDL_LockSurface( gamestate.BackBuffer );

	int dstPitch = gamestate.screen->pitch;
	int pitch = gamestate.BackBuffer->pitch;

	DWORD * dst = ( DWORD * )gamestate.screen->pixels;
	DWORD * src = ( DWORD * )gamestate.BackBuffer->pixels;

	float scaleWidth = gamestate.BackBuffer->w / ( float )destRect.w;
	float scaleHeight = gamestate.BackBuffer->h / ( float )destRect.h; 


	float fSrcX = 0.0f,
		  fSrcY = 0.0f;

	for(int y = destRect.y;  y < destRect.y + destRect.h; y++ )
	{
		fSrcX = 0.0f;

		for(int x = destRect.x ;  x < destRect.x + destRect.w ; x++)
		{
			dst[ (y * dstPitch / 4) + (x) ] = src[ int(fSrcY) * (pitch / 4) + int(fSrcX) ];

			fSrcX += scaleWidth;
		}

		fSrcY += scaleHeight;	
	}

	SDL_UnlockSurface( gamestate.screen );
	SDL_UnlockSurface( gamestate.BackBuffer );

}

// --------------------------------------------------------------------------------------
// blit() - blits offscreen surface to (xpos,ypos) on backbuffer
// --------------------------------------------------------------------------------------
void Gamestate::blit( int index, int xpos, int ypos, bool transparent )
{
	//// Get width & height of surface (in surface desc)
	//DDSURFACEDESC2 ddsd = {0};
	//ddsd.dwSize = sizeof( DDSURFACEDESC2 );
	//m_surfaceList[index]->GetSurfaceDesc( &ddsd );


	// Calc rects
	SDL_Rect srcRect = { 0, 0, m_surfaceList[ index ]->w, m_surfaceList[ index ]->h };
	SDL_Rect destRect = { xpos, ypos, xpos+m_surfaceList[ index ]->w, ypos+m_surfaceList[ index ]->h };


	// Blit!
	if( transparent )
		SDL_BlitSurface(m_surfaceList[index], &destRect, gamestate.screen, &srcRect );
		/*m_lpddsBackbuffer->Blt( &destRect, m_surfaceList[index], &srcRect, DDBLT_WAIT|DDBLT_KEYSRC, 0 );*/
	else
		SDL_BlitSurface(m_surfaceList[index], &destRect, gamestate.screen, &srcRect );

}

// ----------------------------------------------------------------------------
// setUpParallaxLayers() - initializes parallax-struct
// ----------------------------------------------------------------------------
void Gamestate::setUpParallaxLayers()
{
	// Create background
	int i = 0;
	Paralax = new ParallaxBackground();
	Paralax->createLayers( 10 );

	//Firstlayer
	Paralax->setLayer( 0, 0, m_srfBlack, 0, 800, 600, 0, 0, gamestate.BackBuffer->w, gamestate.BackBuffer->h );

	////sky
	Paralax->setLayer( 1, 0.0f, m_srfBack, 0, 800, 400, 0, 0, gamestate.BackBuffer->w, gamestate.BackBuffer->h );

	// trees
	Paralax->setLayer( 2, 0.1f, m_srfTrees, 0, 1172, 170, 0, 370, 800, 170 ); 

	//clouds
	Paralax->setLayer(	3, 0.5f, m_srfClouds, 
						0, 800, 38, 0, 0, gamestate.BackBuffer->w, 
						gamestate.BackBuffer->h );

	Paralax->setLayer(	4, 0.4f, m_srfClouds, 
						38, 800, 87, 0, 38, gamestate.BackBuffer->w, 
						gamestate.BackBuffer->h );

	Paralax->setLayer(	5, 0.3f, m_srfClouds, 
						126, 800, 46, 0, 126, gamestate.BackBuffer->w, 
						gamestate.BackBuffer->h );

	Paralax->setLayer(	6, 0.2f, m_srfClouds, 
						172, 800, 21, 0, 172, gamestate.BackBuffer->w, 
						gamestate.BackBuffer->h );

	Paralax->setLayer(	7, 0.1f, m_srfClouds, 
						193, 800, 12, 0, 193, gamestate.BackBuffer->w, 
						gamestate.BackBuffer->h );

	// City
	Paralax->setLayer( 8, 0.1f, m_srfGrass, 0, 5100, 535, 0, 0, gamestate.BackBuffer->w, gamestate.BackBuffer->h );

	// WalkPath
	Paralax->setLayer(	9, 1.0f, m_srfGrass, 
						540, 5100, 60, 0, 535, gamestate.BackBuffer->w, 
						gamestate.BackBuffer->h );

	///* Fence layer*/
	//Paralax->setLayer(	9, 1.5f,m_srfFence, 0, 256, 26, 
	//					0, GrassHeight-25, gamestate.BackBuffer->w, 
	//					gamestate.BackBuffer->h - GrassHeight);

	gamestate.RecordAllData();

}

/*----------------------------------------------------------
	EOF
----------------------------------------------------------*/
