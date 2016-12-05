/*
Authors: Mario Arturo Lopez, Michael Ibanez, Gregory Bilbrey,
          Kimberly Johnson, Benjamin Milligan
Title : Pokemon Go Group Project
Description:
Created:11/2/2016
Modified:12/4/2016
Due:12/5/2016
Data Abstraction:
    A Plotter is opened with the pixel size 512x1235.
    The opening animation is defined.
    The GameOver sign is defined.
    The background is defined and constructed using its default constructor.
    The phone is defined using its default constructor.
    The trainer is defined using its default constructor.
    The timer is defined using its default constructor.
    The points score is defined using its default constructor.
    The opening animation is defined using its default constructor.
    The 
Output:
    The game begins with an opening animation giving credits to the projects
        creators and any outside sources
    The game is then drawn to the screen with the phone on the right hand side.
    The trainer is drawn to the screen and is redrawn each time it is moved.
    The Pokemon then spawn on the screen using a random spawn function and a
        vector to ensure better randomizing capability.
    After 30 seconds, the game over sign is drawn to the screen with the option
        quit the game or restart it.
Input:
    The user initially presses the Space Bar to get past the opening screen.
    After starting the game, the user presses the arrow keys to move the
        trainer around the screen and catch Pokemon.
    At any time, the user may press the ESC key to exit the game.
Implementation:
Assumptions:
    It is assumed the user will press the arrow keys to move the trainer.
*/

#include "SDL_Plotter.h"
#include "Pokemon.h"
#include "Trainer.h"
#include "myTimer.h"
#include "myPoints.h"                          
#include "Background.h"
#include "Opening_Animation.h"
#include "GameOver.h"

using namespace std;

int main(int argc, char ** argv){

    SDL_Plotter game(512,1235, true);
    Opening_Animation open;
    myTimer timeDisplay;
    myPoints pointDisplay;
    GameOver close;
    Background forest;
    Phone screen;
          
    game.initSound("Caught_Pokemon.wav");
    game.initSound("Background_3.wav");

    int start;
    int stop;
    int caughtCount = 0;
    int pointCount  = 0;

    Pokemon poke;
    Trainer ash;

    char key;

    //Opening Animation
    open.draw(game);
    game.update();

    //Game won't start until Space is pressed
    do{
        if(game.kbhit()){
            key = game.getKey();
            Sleep(50);
        }
    }while(key != ' ');
    game.playSound("Background.wav");
    game.update();
    screen.draw(game);

    //Actual Game /w 60 Second Timer
    do{
    start = time(0);
    while ((!game.getQuit()) && (stop - start <= 60)){
        stop = time(0);

        timeDisplay.setTime(60 - (stop - start));

        if(game.kbhit()){
    	    key = game.getKey();
    	    switch(key){
                case UP_ARROW:    ash.move(UP),
                                  ash.redrawSprite(UP);     //Move Up
                    break;
                case DOWN_ARROW:  ash.move(DOWN),
                                  ash.redrawSprite(DOWN);   //Move Down
                    break;
                case LEFT_ARROW:  ash.move(LEFT),
                                  ash.redrawSprite(LEFT);   //Move Left
                    break;
                case RIGHT_ARROW: ash.move(RIGHT),
                                  ash.redrawSprite(RIGHT);  //Move Right
                    break;
                case 27: exit(1);                           //Quit the Game When Esc. Key is pressed
                    break;
    	    }
    	}

    	//Pokemon spawns after Ash gets within 30 pixels of it
        forest.draw(game);
        poke.draw(game);
        ash.draw(game);

        //Pokemon spawns after Mario gets within 30 pixels of it
        if(abs(ash.getLocX() - poke.getCenteredLocX()) <= 30 &&
           abs(ash.getLocY() - poke.getCenteredLocY())  <= 30)
        {
            poke.draw(game);
            if(abs(ash.getLocX() - poke.getCenteredLocX()) <= 15 &&
               abs(ash.getLocY() - poke.getCenteredLocY()) <= 15)
            {
                //Draw at new location
                game.playSound("Caught_Pokemon.wav");
                poke.moveToMenu(caughtCount%6);
                poke.draw(game);
                game.update();
                poke.caught(game);
                caughtCount++;
                pointCount++;
            }
    	}
    	pointDisplay.setPoints(pointCount);
    	pointDisplay.currentPoints(game);
    	pointDisplay.draw(game);
    	timeDisplay.currentTime(game);
    	timeDisplay.draw(game);
    	game.update();
    }

    close.draw(game);
    game.quitSound("Caught_Pokemon.wav");
    game.update();

    Sleep(2500);

        if(game.kbhit()){
            key = game.getKey();
            Sleep(50);
        }
    }while(key != 'Q' && key == 'N');
    game.quitSound("Background_3.wav");
    game.getQuit();

    return 0;
}
