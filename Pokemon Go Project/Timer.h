#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#include "SDL_Plotter.h"
#include "Background.h"

#include <string>
#include <ctime>
#include <vector>

using namespace std;

//Partially Provided by Dr. Booth
class Timer{
    private:
        Point loc;
        Point oldLoc;
        Point menuLocations[6];
        Color pic[256][256];

        int index;
        int rows, cols;
        vector<string> NumberList;
        string NumberName;
        string currentIndex;
        int time;

    public:
        Timer();
        string chooseTime(vector<string>&);
        int getTime();
        void setTime(int a);
        void draw(SDL_Plotter&);
        void erase(SDL_Plotter&);
        void currentTime(SDL_Plotter&);
};

//Partially provided by Dr. Booth
Timer::Timer(){

    int xPos = 400;
    for(int i = 0; i < 6; i++){
        menuLocations[i].x = xPos;
        menuLocations[i].y = 1300;
        xPos+= 31;
    }

    ifstream input(NumberList[1].c_str());

    input >> rows >> cols;
    for(int r = 0; r < rows; r++){
        for(int c = 0; c < cols; c++){
            input >> pic[r][c].R;
            input >> pic[r][c].G;
            input >> pic[r][c].B;
        }
    }
    input.close();
}

//Chooses random Pokemon from list
string Timer::chooseTime(vector<string>& NumberList){
    string currentIndex;
    ifstream getList("NumberList");
    while(getList >> currentIndex)
        NumberList.push_back(currentIndex);
    int a = getTime();
    return NumberList[a];
}

void Timer::currentTime(SDL_Plotter& g){
    NumberName = chooseTime(NumberList);

    ifstream input(NumberName.c_str());
    input >> rows >> cols;
    for(int r = 0; r < rows; r++){
        for(int c = 0; c < cols; c++){
            input >> pic[r][c].R;
            input >> pic[r][c].G;
            input >> pic[r][c].B;
        }
    }
    input.close();
    erase(g);
}

//Draws Pokemon (Cuts out white corners)
//Partially provided by Dr. Booth
void Timer::draw(SDL_Plotter& g){
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
                //If pixel is not white
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


//Erases Pokemon
//Provided by Dr. Booth
void Timer::erase(SDL_Plotter& g){
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

int Timer::getTime(){
    return time;
}
void Timer::setTime(int a){
    int time = a;
}

#endif // POKEMON_H_INCLUDED
