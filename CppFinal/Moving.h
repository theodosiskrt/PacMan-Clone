#ifndef MOVING_H
#define MOVING_H

#include <iostream>
#include <vector>
#include <curses.h>
#include <panel.h>

using namespace std;

class Moving
{
private:
    int posX, posY;

public:
    Moving();
    void setPosX(int);
    void setPosY(int);
    int getPosX();
    int getPosY();
    bool checkMove(int, vector<vector<char>>, char );
};

#endif
