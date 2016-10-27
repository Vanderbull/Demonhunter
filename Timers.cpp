#include "Timers.h"
#include "SDL.h"
Timer timer;

// Fredik Zaar SP6 Demon Hunter

Timer::Timer()
{
	AttackTimer_Skeleton = 0.0f;
	AttackTimer_Zombie = 0.0f;
	AttackTimer_Head = 0.0f;

	Timer_AttackBoss = 0.0f;
	Timer_BossAnim = 0.0f;
	Timer_BossHead = 0.0f;
	Timer_Dancing = 0.0f;

	Timer_PowerUp = 0.0f;
	Timer_CoffinTimer = 0.0f;
	Timer_PowerUpRoll = 0.0f;
	Timer_MorphPics = 0.0f;

	Timer_TriangleAttack = 0.0f;
	Timer_Health = 0.0f;
	Timer_UpdateGame = 0.0f;
	Timer_CreateCoffin = 0.0f;

	Timer_Hit = 0.0f;
	Timer_Immortal = 0.0f;

	Timer_R = 0.0f; 
	Timer_G = 0.0f; 
	Timer_B = 0.0f;
	Timer_Color = 0.0f;

	Timer_ShowDead = 0.0f;
	Timer_Name = 0.0f;

	Timer_FireBall = 0.0f;
	Timer_TriangleAttack = 0.0f;

	startTicks = 0;
    pausedTicks = 0;
    paused = false;
    started = false;   


}

void Timer::RestartAllTimers()
{
	AttackTimer_Skeleton = 0.0f;
	AttackTimer_Zombie = 0.0f;
	AttackTimer_Head = 0.0f;

	Timer_AttackBoss = 0.0f;
	Timer_BossAnim = 0.0f;
	Timer_BossHead = 0.0f;

	Timer_PowerUp = 0.0f;
	Timer_CoffinTimer = 0.0f;
	Timer_PowerUpRoll = 0.0f;
	Timer_MorphPics = 0.0f;

	Timer_TriangleAttack = 0.0f;
	Timer_Health = 0.0f;
	Timer_UpdateGame = 0.0f;
	Timer_CreateCoffin = 0.0f;

	Timer_Hit = 0.0f;
	Timer_Immortal = 0.0f;

	Timer_R = 0.0f; 
	Timer_G = 0.0f; 
	Timer_B = 0.0f;
	Timer_Color = 0.0f;

	Timer_ShowDead = 0.0f;

	startTicks = 0;
    pausedTicks = 0;
    paused = false;
    started = false;   

}

void Timer::start()
{
    //Start the timer
    started = true;
    
    //Unpause the timer
    paused = false;
    
    //Get the current clock time
    startTicks = SDL_GetTicks();    
}

void Timer::stop()
{
    //Stop the timer
    started = false;
    
    //Unpause the timer
    paused = false;    
}

void Timer::pause()
{
    //If the timer is running and isn't already paused
    if( ( started == true ) && ( paused == false ) )
    {
        //Pause the timer
        paused = true;
    
        //Calculate the paused ticks
        pausedTicks = SDL_GetTicks() - startTicks;
    }
}

void Timer::unpause()
{
    //If the timer is paused
    if( paused == true )
    {
        //Unpause the timer
        paused = false;
    
        //Reset the starting ticks
        startTicks = SDL_GetTicks() - pausedTicks;
        
        //Reset the paused ticks
        pausedTicks = 0;
    }
}

int Timer::get_ticks()
{
    //If the timer is running
    if( started == true )
    {
        //If the timer is paused
        if( paused == true )
        {
            //Return the number of ticks when the the timer was paused
            return pausedTicks;
        }
        else
        {
            //Return the current time minus the start time
            return SDL_GetTicks() - startTicks;
        }    
    }
    
    //If the timer isn't running
    return 0;    
}

bool Timer::is_started()
{
    return started;    
}

bool Timer::is_paused()
{
    return paused;    
}