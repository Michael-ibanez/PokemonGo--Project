#ifndef PHONE_H_INCLUDED
#define PHONE_H_INCLUDED

//Screen Size 195 x 389

#include "SDL_Plotter.h"

using namespace std;

class Phone{
    private:
        Point loc;
        vector<vector<Color> > ph;
        int rows, cols;

    public:
       /*
        * description: default constructor for the Phone
        * return: default Phone
        * precondition: none
        * postcondition: default Phone is constructed
        */
        Phone();
        
       /*
        * description: returns the Point location of the Phone
        * return: Point
        * precondition: none
        * postcondition: Point location is returned
        */
        Point getLoc();
        
       /*
        * description: draws the phone
        * return: none
        * precondition: none
        * postcondition: phone is drawn to the screen
        */
        void draw(SDL_Plotter&);
};

Point Phone::getLoc(){
    return loc;
}

Phone::Phone(){
    ph.resize(512, vector<Color>(1235));
    ifstream file("Screen");
    loc.x = 1028;
    loc.y = 163;
    file >> rows >> cols;
    for(int r = 0; r < rows; r++){
        for(int c = 0; c < cols; c++){
            file >> ph[r][c].R;
            file >> ph[r][c].G;
            file >> ph[r][c].B;
        }
    }
    file.close();
}

void Phone::draw(SDL_Plotter& g){
    for(int r = 0; r < rows; r++){
        for(int c = 0; c < cols; c++){
            g.plotPixel(loc.x + c, loc.y + r,
                        ph[r][c].R,
                        ph[r][c].G,
                        ph[r][c].B);
        }
    }
}

#endif // PHONE_H_INCLUDED
