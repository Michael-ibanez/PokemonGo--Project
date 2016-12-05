#ifndef OPENING_ANIMATION_H_INCLUDED
#define OPENING_ANIMATION_H_INCLUDED

#include "SDL_Plotter.h"
#include "Background.h"

using namespace std;

class Opening_Animation{
    private:
        Point loc;
        Point oldLoc;
        vector<vector<Color> > oa;
        int rows, cols;

    public:
         /*
        * description: default constructor
        * return: default opening animation
        * precondition: N/A
        * postcondition: N/A
        */
        Opening_Animation();
    
         /*
        * description: getter function
        * return: location
        * precondition: location exists within opening animation object
        * postcondition: location remains unchanged
        */
        Point getLoc();
    
         /*
        * description: getter function
        * return: vector
        * precondition: integers r and c exist
        * postcondition: color at position r and c remains unchanged
        */
        int getR(int r, int c);
    
         /*
        * description: getter function
        * return: vector
        * precondition: integers r and c exist
        * postcondition: color at position r and c remains unchanged
        */
        int getG(int r, int c);
    
        /*
        * description: getter function
        * return: vector
        * precondition: integers r and c exist
        * postcondition: color at position r and c remains unchanged
        */
        int getB(int r, int c);
    
        /*
        * description: draw function
        * return: N/A
        * precondition: plotter function exists
        * postcondition: plots color at position r and c in the vector
        */
        void draw(SDL_Plotter&);
};

Point Opening_Animation::getLoc(){
    return loc;
}

int Opening_Animation::getR(int r, int c){
    return oa[r][c].R;
}

int Opening_Animation::getG(int r, int c){
    return oa[r][c].G;
}

int Opening_Animation::getB(int r, int c){
    return oa[r][c].B;
}

Opening_Animation::Opening_Animation(){
    oa.resize(512, vector<Color>(1235));
    ifstream file("Opening_Animation");
    loc.x = 0;
    loc.y = 0;
    oldLoc = loc;
    file >> rows >> cols;
    for(int r = 0; r < rows; r++){
        for(int c = 0; c < cols; c++){
            file >> oa[r][c].R;
            file >> oa[r][c].G;
            file >> oa[r][c].B;
        }
    }
    file.close();
}

void Opening_Animation::draw(SDL_Plotter& g){
    for(int r = 0; r < rows; r++){
        for(int c = 0; c < cols; c++){
            g.plotPixel(loc.x + c, loc.y + r,
                        oa[r][c].R,
                        oa[r][c].G,
                        oa[r][c].B);
        }
    }
}

#endif // OPENING_ANIMATION_H_INCLUDED
