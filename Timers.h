#pragma once

class Timer
{
public:
	Timer();

	bool is_paused();
	bool is_started();
	int	 get_ticks();
	void unpause();
	void pause();
	void stop();
	void start();
	void RestartAllTimers();

	float AttackTimer_Skeleton;
	float AttackTimer_Zombie;
	float AttackTimer_Head;
	float Timer_CreateCoffin;

	float Timer_AttackBoss;
	float Timer_BossAnim;
	float Timer_BossHead;
	float Timer_CoffinTimer;

	float Timer_PowerUp;
	float Timer_PowerUpRoll;

	float Timer_MorphPics;
	float Timer_TriangleAttack;

	float Timer_Health;
	float Timer_UpdateGame;

	float Timer_Hit;
	float Timer_Immortal;

	float Timer_R; 
	float Timer_G; 
	float Timer_B;
	float Timer_Color;

	float Timer_ShowDead;
	float Timer_Name;
	float Timer_Dancing;

	float Timer_FireBall;
	float Timer_TriangleAttackOK;

private:
	//The clock time when the timer started
    int startTicks;
    
    //The ticks stored when the timer was paused
    int pausedTicks;
    
    //The timer status
    bool paused;
    bool started;
};

extern Timer timer;
