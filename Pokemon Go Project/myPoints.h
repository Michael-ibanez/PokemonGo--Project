#ifndef MYPOINTS_H_INCLUDED
#define MYPOINTS_H_INCLUDED

#include "SDL_Plotter.h"
#include "Trainer.h"
#include "Background.h"

#include <string>
#include <ctime>
#include <vector>

using namespace std;

class myPoints{
    private:
        Point loc;
        vector<vector<Color> > image;

        int rows, cols;
        int points;

        vector<string> pointList;
        string pointName;

    public:
       /*
        * description: default constructor for the Pokemon
        * return: default Pokemon
        * precondition: none
        * postcondition: default Pokemon is constructed
        */
        myPoints();

       /*
        * description: chooses a Pokemon from a list
        * return: string
        * precondition: must be a Pokemon list
        * postcondition: returns a random Pokemon
        */
        string choosePoints(vector<string>&);

       /*
        * description: draws a Pokemon the screen
        * return: none
        * precondition: must pass in a plotter and must have a Pokemon to draw and pass in a plotter
        * postcondition: returns int that better centers the Pokemon
        */
        void draw(SDL_Plotter&);

       /*
        * description: spawns a new Pokemon when the previous one is caught
        * return: none
        * precondition: trainer must have the same location as Pokemon and pass in a plotter
        * postcondition: a new Pokemon is spawned in a new location
        */
        void currentPoints(SDL_Plotter&);

       /*
        * description: erases the Pokemon
        * return: none
        * precondition: must have a Pokemon to erase and pass in a plotter
        * postcondition: Pokemon gets erased
        */
        void erase(SDL_Plotter&);

        int getPoints();

        void setPoints(int a);
};

//Partially provided by Dr. Booth
myPoints::myPoints(){
    image.resize(256, vector<Color>(256));
    pointName = choosePoints(pointList);

    ifstream input("Number_00.txt");

    loc.x = 1040;
    loc.y = 170;

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


//Chooses random Pokemon from list
string myPoints::choosePoints(vector<string>& pointList){
    string currentIndex;
    ifstream getList("PointList");
    while(getList >> currentIndex)
        pointList.push_back(currentIndex);

    return pointList[getPoints()];
}

//Draws Pokemon (Cuts out white corners)
//Partially provided by Dr. Booth
void myPoints::draw(SDL_Plotter& g){
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

//Spawns a new Pokemon when current Pokemon is caught
void myPoints::currentPoints(SDL_Plotter& g){
    pointName = choosePoints(pointList);

    ifstream input(pointName.c_str());
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

//Erases Pokemon
//Provided by Dr. Booth
void myPoints::erase(SDL_Plotter& g){
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
int myPoints::getPoints(){
    return points;
}

void myPoints::setPoints(int a){
    points = a;
}


#endif // MYPOINTS_H_INCLUDED
