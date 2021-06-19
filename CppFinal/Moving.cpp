#include "Moving.h"

Moving::Moving()
{
}

void Moving::setPosX(int posX) { this->posX = posX; }
void Moving::setPosY(int posY) { this->posY = posY; }
int Moving::getPosX() { return this->posX; }
int Moving::getPosY() { return this->posY; }

bool Moving::checkMove(int input, vector<vector<char> > maze, char symbol)
{
    switch (input)
    {
    case KEY_UP:
        // cout << "IN UP ";
        if (maze[this->getPosY() - 1][this->getPosX()] != '*')
        {
          if((symbol == 'G' && maze[this->getPosY() - 1][this->getPosX()] != 'T') || (symbol == 'T' && maze[this->getPosY() - 1][this->getPosX()] != 'G') || symbol == 'P')
            return true;
        }
        break;
    case KEY_DOWN:
        // cout << "IN DOWN ";
        if (maze[this->getPosY() + 1][this->getPosX()] != '*')
        {
          if((symbol == 'G' && maze[this->getPosY() + 1][this->getPosX()] != 'T') || (symbol == 'T' && maze[this->getPosY() + 1][this->getPosX()] != 'G') || symbol == 'P')
            // cout << "CHECKING DOWN " << this->getPosY() + 1 << " " << this->getPosX()
            // << "                 ";
            return true;
        }
        break;
    case KEY_LEFT:
        // cout << "IN LEFT ";
        if (maze[this->getPosY()][this->getPosX() - 1] != '*')
        {
          if((symbol == 'G' && maze[this->getPosY()][this->getPosX() - 1] != 'T') || (symbol == 'T' && maze[this->getPosY()][this->getPosX() - 1] != 'G') || symbol == 'P')

            // cout << "CHECKING LEFT " << this->getPosY() << " " << this->getPosX() - 1 << "                 ";
            return true;
        }
        break;

    case KEY_RIGHT:
        // cout << "IN RIGHT ";
        if (maze[this->getPosY()][this->getPosX() + 1] != '*')
        {
          if((symbol == 'G' && maze[this->getPosY()][this->getPosX() + 1] != 'T') || (symbol == 'T' && maze[this->getPosY()][this->getPosX() + 1] != 'G') || symbol == 'P')

            // cout << "CHECKING RIGHT " << this->getPosY() << " " << this->getPosX() + 1 << "                 ";
            return true;
        }
        break;
    case ' ':
        return true;
        break;
    case 27:
        return true;
        break;
    }
    return false;
}
