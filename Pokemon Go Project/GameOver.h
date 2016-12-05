#ifndef GAMEOVER_H_INCLUDED
#define GAMEOVER_H_INCLUDED

#include "SDL_Plotter.h"
#include "Background.h"

using namespace std;

class GameOver{
    private:
        Point loc;
        vector<vector<Color> > window;
        int rows, cols;

    public:
        
        /*
        * description: default constructor
        * return: default GameOver picture
        * precondition: none
        * postcondition: GameOver is constructed
        */
        GameOver();
        
        /*
        * description: gets the location to draw the game over message
        * return: Point
        * precondition: none
        * postcondition: location to draw game over message is returned
        */
        Point getLoc();
        
        /*
        * description: draws the game over sign
        * return: none
        * precondition: must pass in a plotter to draw the pixels
        * postcondition: game over is drawn to the screen
        */
        void draw(SDL_Plotter&);
        
        /*
        * description: erases the game over sign 
        * return: none
        * precondition: must pass in a plotter to erase the pizels
        * postcondition: game over is erased
        */
        void erase(SDL_Plotter&);
};

Point GameOver::getLoc(){
    return loc;
}

GameOver::GameOver(){
    window.resize(512, vector<Color>(1235));
    ifstream file("GameOver_Animation");
    loc.x = 105;
    loc.y = 110;
    file >> rows >> cols;
    for(int r = 0; r < rows; r++){
        for(int c = 0; c < cols; c++){
            file >> window[r][c].R;
            file >> window[r][c].G;
            file >> window[r][c].B;
        }
    }
    file.close();
}

void GameOver::draw(SDL_Plotter& g){
    for(int r = 0; r < rows; r++){
        for(int c = 0; c < cols; c++){
            g.plotPixel(loc.x + c, loc.y + r,
                        window[r][c].R,
                        window[r][c].G,
                        window[r][c].B);
        }
    }
}

void GameOver::erase(SDL_Plotter& g){
    for(int r = 0; r < rows; r++){
        for(int c = 0; c < cols; c++){
            if(loc.x + c >= 0 && loc.y + r >= 0 &&
               loc.x + c < 960 && loc.y + r < 512)
            {
                g.plotPixel(loc.x + c, loc.y + r,
                current.getR(r, c),
                current.getG(r, c),
                current.getB(r, c));
            }
        }
    }
}

#endif // GAMEOVER_H_INCLUDED
