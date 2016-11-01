#pragma once
#include <string>

#include <SDL.h>

using namespace std;

enum{ MYDUDE, MYDUDE_DEMON, FATHER };

class DancingDragon
{
public:
	DancingDragon( int Surface );
	int xPos, yPos;
	int Height, Width;
	int Frame, PrevFrame;
	int surface;
	int StateCounter;
	void SetFrame();
	void SetClips();
	SDL_Rect Clips[ 23 ];
};

class IntroTalk
{
public:
	IntroTalk( int Surface );

	int xPos, yPos;
	int Height, Width;
	int surface;
	int LetterHeight, LetterWidth, y;
	int Letter;

	int CounterWords, CounterNextTalker, Counter;
	SDL_Rect srcClips[ 3 ];
	SDL_Rect DestClips[ 3 ];
	int Frame;
	int Line;

	string My_DudeTalks[ 4 ];
	string My_FatherTalks[ 4 ];

	void DrawBackground();

	string My_DudeTalksSlow[ 5 ];
	string My_DudeTalksSlow2[ 5 ];
	string My_DudeTalksSlow3[ 5 ];
	string My_DudeTalksSlow4[ 5 ];

	string My_FatherTalksSlow[ 5 ];
	string My_FatherTalksSlow2[ 5 ];
	string My_FatherTalksSlow3[ 5 ];
	string My_FatherTalksSlow4[ 5 ];

	void DoTalk();

	bool MyDude, Father, MyDude_Demon, FirstLine, SecondLine, ThirdLine, FourthLine, Fifth,
		Sixth, Seventh, Eight;

	SDL_Surface * IntroSurfaces[ 1 ];
};
