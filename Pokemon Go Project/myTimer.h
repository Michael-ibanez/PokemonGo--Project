#ifndef MYTIMER_H_INCLUDED
#define MYTIMER_H_INCLUDED

#include "SDL_Plotter.h"
#include "Trainer.h"
#include "Background.h"

#include <string>
#include <ctime>
#include <vector>

using namespace std;

class myTimer{
    private:
        Point loc;
        vector<vector<Color> > image;

        int rows, cols;
        int currentTiming;

        vector<string> NumberList;
        string numberName;

    public:
       /*
        * description: default constructor for the timer
        * return: default timer
        * precondition: none
        * postcondition: default Timer is constructed
        */
        myTimer();

       /*
        * description: chooses a time from a list of image
        * return: string
        * precondition: must have a time
        * postcondition: returns time to draw
        */
        string chooseTime(vector<string>&);

       /*
        * description: draws the timer on the screen
        * return: none
        * precondition: must pass in a plotter
        * postcondition: draws timer
        */
        void draw(SDL_Plotter&);

       /*
        * description: holds the current time to draw
        * return: none
        * precondition: none
        * postcondition: time is passed to draw
        */
        void currentTime(SDL_Plotter&);

       /*
        * description: erases the timer
        * return: none
        * precondition: must pass in a plotter to erase the pizels
        * postcondition: timer is erased
        */
        void erase(SDL_Plotter&);

        /*
        * description: gives the current time
        * return: int
        * precondition: none
        * postcondition: current time is returned
        */
        int getTime();

        /*
        * description: sets the current time
        * return: none
        * precondition: none
        * postcondition: current time is set
        */
        void setTime(int a);
};

//Partially provided by Dr. Booth
myTimer::myTimer(){
    image.resize(256, vector<Color>(256));
    numberName = chooseTime(NumberList);

    ifstream input("Number_00.txt");

    loc.x = 1036;
    loc.y = 78;

    input >> rows >> cols;
    for(int r = 0; r < rows; r++){
        for(int c = 0; c < cols; c++){
            input >> image[r][c].R;
            input >> image[r][c].G;
            input >> image[r][c].B;
        }
    }
    input.close();
}


//Chooses Time from list
string myTimer::chooseTime(vector<string>& NumberList){
    string currentIndex;
    ifstream getList("NumberList");
    while(getList >> currentIndex)
        NumberList.push_back(currentIndex);

    return NumberList[getTime()];
}

//Draws Time (cuts white corners)
//Partially provided by Dr. Booth
void myTimer::draw(SDL_Plotter& g){
    erase(g);
    for(int r = 0; r < rows; r++){
        for(int c = 0; c < cols; c++){
            if(loc.x + c >= 0  &&
               loc.y + r >= 0  &&
               loc.x + c < 1500 &&
               loc.y + r < 512)
            {
                //If pixel is white
                if(image[r][c].R < 255 &&
                   image[r][c].G < 255 &&
                   image[r][c].B < 255)
                {
                    //Draw pixel of background instead
                    g.plotPixel(loc.x + c, loc.y + r,
                    image[r][c].R,
                    image[r][c].G,
                    image[r][c].B);
                }
                //If pixel is not white
                else if(image[r][c].R == 256 &&
                        image[r][c].G == 256 &&
                        image[r][c].B == 256)
                {
                    g.plotPixel(loc.x + c, loc.y + r,
                    image[r][c].R,
                    image[r][c].G,
                    image[r][c].B);
                }
            }
        }
    }
}

//Holds current time
void myTimer::currentTime(SDL_Plotter& g){
    numberName = chooseTime(NumberList);

    ifstream input(numberName.c_str());
    input >> rows >> cols;
    for(int r = 0; r < rows; r++){
        for(int c = 0; c < cols; c++){
            input >> image[r][c].R;
            input >> image[r][c].G;
            input >> image[r][c].B;
        }
    }
    input.close();
    erase(g);
}

//Erases part of the Timer to prevent overlap
//Provided by Dr. Booth
void myTimer::erase(SDL_Plotter& g){
    for(int r = 0; r < rows; r++){
        for(int c = 0; c < cols; c++){
            if(loc.x + c >= 0  &&
               loc.y + r >= 0  &&
               loc.x + c < 960 &&
               loc.y + r < 512)
            {
                g.plotPixel(loc.x + c, loc.y + r,
                current.getR(r, c),
                current.getG(r, c),
                current.getB(r, c));
            }
        }
    }
}
int myTimer::getTime(){
    return currentTiming;
}

void myTimer::setTime(int a){
    currentTiming = a;
}

#endif // MYTIMER_H_INCLUDED
