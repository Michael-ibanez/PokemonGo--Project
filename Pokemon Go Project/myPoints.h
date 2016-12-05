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
        * description: default constructor for the Points
        * return: default Points
        * precondition: none
        * postcondition: default Points are constructed
        */
        myPoints();

       /*
        * description: chooses a Points png from a list
        * return: string
        * precondition: must be a Points list
        * postcondition: returns the Points file
        */
        string choosePoints(vector<string>&);

       /*
        * description: draws the Points to the screen
        * return: none
        * precondition: must pass in a plotter and must have points to draw
        * postcondition: draws the points to the screen
        */
        void draw(SDL_Plotter&);

       /*
        * description: holds how many points the user has
        * return: none
        * precondition: none
        * postcondition: gives the current points to be drawn
        */
        void currentPoints(SDL_Plotter&);

       /*
        * description: erases the points
        * return: none
        * precondition: must have a points to erase and pass in a plotter
        * postcondition: points get erased
        */
        void erase(SDL_Plotter&);

        /*
        * description: gives the current points
        * return: int
        * precondition: none
        * postcondition: current points are returned
        */
        int getPoints();

        /*
        * description: sets the current points
        * return: none
        * precondition: none
        * postcondition: current points are set
        */
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


//Chooses Points from list
string myPoints::choosePoints(vector<string>& pointList){
    string currentIndex;
    ifstream getList("PointList");
    while(getList >> currentIndex)
        pointList.push_back(currentIndex);

    return pointList[getPoints()];
}

//Draws Points (cuts white corners)
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

//Holds crurrent points
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

//Erases Points
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
