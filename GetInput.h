#pragma once
#include <string>

#include "SDL.h"

//The key press interpreter
class StringInput
{  
    public:
    //Initializes variables
    StringInput();
    
    //Does clean up
    ~StringInput();
    
    //Handles input
    void handle_input( SDL_Event event );
    
    //Shows the message on screen
    void show_centered();    

	//The storage string
    std::string str;

    private:

    //The text surface
    SDL_Surface *text;
};
