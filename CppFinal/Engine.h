#include <iostream>
#include <fstream>
#include <vector>
#include <curses.h>
#include <panel.h>
#include "Potter.h"
#include "Gnome.h"
#include "Traal.h"
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "HiScore.h"

using namespace std;

class Engine
{
private:
    ifstream *mazeFile;
    vector<vector<char> > maze;
    int marginX, marginY;
    bool wasEmeraldGnome;
    bool wasEmeraldTraal;
    bool end;
    bool fullExit;
    int playerScore;
    Potter potter;
    Gnome gnome;
    Traal traal;
    HiScore *hiScore;
    string finalNotif;
    string playerName;
public:
    Engine(ifstream &, ifstream &, string);
    void initMaze();
    void initEntity(Moving &,  char);
    void initGems();
    void startGame();
    void initVellum();
    void moveEntity(int, Moving &, char);
    void checkForGem();
    void checkAndInitVellum();
    void checkWin();
    void calculateAndMoveEnemy(Moving &, char);
    void showEndScreen();
    void updateHiScores();
    void getName();

};
