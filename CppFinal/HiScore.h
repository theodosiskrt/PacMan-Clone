#include <iostream>
#include <curses.h>
#include <panel.h>
#include <sstream>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <fstream>





using namespace std;

class HiScore
{
private:
    int topBorder;
    int bottomBorder;
    int leftBorder;
    int rightBorder;
    int middleBorder;
    string hiScores[5][2];
    string scoresFileName;
public:
  HiScore(string);
  string getHighScore(int, int);
  void setHighScore(int, int, string);
  void showHiScores(int);
  void updatePlayerScore(int);
  void readHiScores(ifstream &);
  void initHiScores();
  void updateHiScores(int, string);
};
