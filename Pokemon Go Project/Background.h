#ifndef BACKGROUND_H_INCLUDED
#define BACKGROUND_H_INCLUDED

#include "Pokemon.h"
#include "Trainer.h"
#include "SDL_Plotter.h"

#include <fstream>

using namespace std;

char c;

//Provided by Dr. Booth
struct Point{
    int x, y;
    Point(int x = 0, int y = 0);
};

//Provided by Dr. Booth
struct Color{
    int R, G, B;

    Color(){
        R = G = B = 255;
    }
};

//Partially provided by Dr. Booth
class Background{
    private:
        Point loc;
        vector<vector<Color> > mapTemplate;
        int rows, cols;

    public:
        Background();
        Point getLoc();
        int getR(int r, int c);
        int getG(int r, int c);
        int getB(int r, int c);
        void draw(SDL_Plotter&);
};

//Provided by Dr. Booth
Point::Point(int a, int b){
    x = a;
    y = b;
}

Point Background::getLoc(){
    return loc;
}

int Background::getR(int r, int c){
    return mapTemplate[r][c].R;
}

int Background::getG(int r, int c){
    return mapTemplate[r][c].G;
}

int Background::getB(int r, int c){
    return mapTemplate[r][c].B;
}

Background::Background(){
    mapTemplate.resize(512, vector<Color>(1235));
    ifstream file("Forest_Background");
    loc.x = 0;
    loc.y = 0;
    file >> rows >> cols;
    for(int r = 0; r < rows; r++){
        for(int c = 0; c < cols; c++){
            file >> mapTemplate[r][c].R;
            file >> mapTemplate[r][c].G;
            file >> mapTemplate[r][c].B;
        }
    }
    file.close();
}

void Background::draw(SDL_Plotter& g){
    for(int r = 0; r < rows; r++){
        for(int c = 0; c < cols; c++){
            g.plotPixel(loc.x + c, loc.y + r,
                        mapTemplate[r][c].R,
                        mapTemplate[r][c].G,
                        mapTemplate[r][c].B);
        }
    }
}

#endif // BACKGROUND_H_INCLUDED
