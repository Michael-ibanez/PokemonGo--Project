#ifndef TRAINER_H_INCLUDED
#define TRAINER_H_INCLUDED

#include "Background.h"
#include "Pokemon.h"
#include "SDL_Plotter.h"

enum DIR {UP, DOWN, LEFT, RIGHT, THROW};
enum RGB {R, G, B};

Background current;

using namespace std;

//Partially provided by Dr. Booth
class Trainer{
    private:
        Point loc;
        Point oldLoc;
        Color pic[256][256];

        int speed;
        int rows, cols;

    public:
    
        /*
        * description: default constructor for the Trainer
        * return: default Trainer
        * precondition: none
        * postcondition: Trainer is constructed using default values
        */        
        Trainer();

        /*
        * description: returns the loc.x of the trainer
        * return: int
        * precondition: must have a loc.x
        * postcondition: returns the int value of loc.x
        */
        int getLocX();

        /*
        * description: returns the loc.y of the trainer
        * return: int
        * precondition: must have a loc.y
        * postcondition: returns the int value of loc.y
        */
        int getLocY();

        /*
        * description: draws a Trainer the screen
        * return: none
        * precondition: must pass in a plotter and have a trainer picture to draw
        * postcondition: draws the trainer to the screen
        */
        void draw(SDL_Plotter&);

        /*
        * description: erases the Trainer's previous position on the screen
        * return: none
        * precondition: must pass in a plotter
        * postcondition: erases the trainer from the screen
        */
        void erase(SDL_Plotter&);

        /*
        * description: moves the trainer according to the key pressed
        * return: none
        * precondition: must pass in a direction to move the trainer in
        * postcondition: moves the trainer on the screen
        */
        void move(DIR);

        /*
        * description: redraws the trainer according to the key pressed
        * return: none
        * precondition: must pass in a direction to redraw the trainer in
        * postcondition: redraws the trainer on the screen
        */
        void redrawSprite(DIR);
};

//Partially provided by Dr. Booth
Trainer::Trainer(){
    ifstream file("Trainer_Still_Backward");
    file >> rows >> cols;
    for(int r = 0; r < rows; r++){
        for(int c = 0; c < cols; c++){
            file >> pic[r][c].R;
            file >> pic[r][c].G;
            file >> pic[r][c].B;
        }
    }
    file.close();

    loc.x = 200;
    loc.y = 200;
    oldLoc = loc;
    speed = 10;
}

//Returns current X coordinate of Trainer
int Trainer::getLocX(){
    return loc.x;
}

//Returns current X coordinate of Trainer
int Trainer::getLocY(){
    return loc.y;
}

//Draws Trainer
//Partially provided by Dr. Booth
void Trainer::draw(SDL_Plotter& g){
    erase(g);
    for(int r = 0; r < rows; r++){
        for(int c = 0; c < cols; c++){
            if(loc.x + c >= 0  &&
               loc.y + r >= 0  &&
               loc.x + c < 960 &&
               loc.y + r < 512)
            {
                //If pixel is white
                if(pic[r][c].R < 255 &&
                   pic[r][c].G < 255 &&
                   pic[r][c].B < 255)
                {
                    //Draw pixel of background instead
                    g.plotPixel(loc.x + c, loc.y + r,
                    pic[r][c].R,
                    pic[r][c].G,
                    pic[r][c].B);
                }

                else if(pic[r][c].R == 255 &&
                        pic[r][c].G == 255 &&
                        pic[r][c].B == 255)
                {
                    g.plotPixel(loc.x + c, loc.y + r,
                    current.getR(r, c),
                    current.getG(r, c),
                    current.getB(r, c));
                }
            }
        }
    }
}

//Erases Trainer
//Partially provided by Dr.Booth
void Trainer::erase(SDL_Plotter& g){
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

//Moves the Trainer while staying within the bounds of the game
//Partially Provided by Dr. Booth
void Trainer::move(DIR d){
    oldLoc = loc;
    switch(d){
        //Remember: Left/Right is X and Up/Down is Y
        case UP:   if((loc.y-1 >= 80  &&
                     ((loc.x   >= 50  && loc.x <= 80)    ||
                      (loc.x   >= 860 && loc.x <= 900))) ||
                      (loc.y-1 >= 60  &&
                      (loc.x   >= 80  && loc.x <= 860)))

                      {
                          loc.y-= speed;
                      }
            break;

        case DOWN: if((loc.y+1 <= 483 &&
                     ((loc.x   >= 50  && loc.x  <= 80)    ||
                      (loc.x   >= 860 && loc.x  <= 900))) ||
                      (loc.y+1 <= 373 &&
                      (loc.x   >= 80  && loc.x <= 860)))

                      {
                        loc.y+= speed;
                      }

            break;

        case LEFT: if((((loc.x-1 >= 50  && loc.x-1 <= 80)    ||
                        (loc.x-1 >= 860 && loc.x-1 <= 900))  &&
                        (loc.y   >= 80  && loc.y   <= 493))  ||
                        (loc.x-1 >= 80  && loc.x-1 <= 860    &&
                         loc.y   >= 60  && loc.y   <= 383))

                         {
                            loc.x-= speed;
                         }
            break;

        case RIGHT: if((((loc.x+1 >= 50  && loc.x+1 <= 80)   ||
                         (loc.x+1 >= 860 && loc.x+1 <= 900)) &&
                         (loc.y   >= 80  && loc.y   < 493))  ||
                         (loc.x+1 >= 80  && loc.x+1 <= 860   &&
                          loc.y   >= 60  && loc.y   < 383))

                         {
                            loc.x+= speed;
                         }
            break;
    }
}

//Switches position (sprite) of Trainer (Braces are important - DO NOT DELETE)
void Trainer::redrawSprite(DIR d){
    oldLoc = loc;
    switch(d){
        case UP:{ ifstream file("Trainer_Still_Backward");
                        file >> rows >> cols;
                        for(int r = 0; r < rows; r++){
                            for(int c = 0; c < cols; c++){
                                file >> pic[r][c].R;
                                file >> pic[r][c].G;
                                file >> pic[r][c].B;
                            }
                        }
                        file.close();
        }
                break;
        case DOWN:{ ifstream file("Trainer_Still_Forward");
                        file >> rows >> cols;
                        for(int r = 0; r < rows; r++){
                            for(int c = 0; c < cols; c++){
                                file >> pic[r][c].R;
                                file >> pic[r][c].G;
                                file >> pic[r][c].B;
                            }
                        }
                        file.close();
        }
                break;
        case LEFT:{ ifstream file("Trainer_Still_Left");
                        file >> rows >> cols;
                        for(int r = 0; r < rows; r++){
                            for(int c = 0; c < cols; c++){
                                file >> pic[r][c].R;
                                file >> pic[r][c].G;
                                file >> pic[r][c].B;
                            }
                        }
                        file.close();
        }
                break;
        case RIGHT:{ ifstream file("Trainer_Still_Right");
                        file >> rows >> cols;
                        for(int r = 0; r < rows; r++){
                            for(int c = 0; c < cols; c++){
                                file >> pic[r][c].R;
                                file >> pic[r][c].G;
                                file >> pic[r][c].B;
                            }
                        }
                        file.close();
        }
                break;
        case THROW:{ ifstream file("Trainer_Throw");
                        file >> rows >> cols;
                        for(int r = 0; r < rows; r++){
                            for(int c = 0; c < cols; c++){
                                file >> pic[r][c].R;
                                file >> pic[r][c].G;
                                file >> pic[r][c].B;
                            }
                        }
                        file.close();
        }
                break;
    }
}

#endif // TRAINER_H_INCLUDED
