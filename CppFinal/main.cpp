#include <iostream>
#include <ctype.h>
#include "Engine.h"


using namespace std;

int main(int argc, char *argv[])
{
    srand(static_cast<unsigned int>(time(nullptr)));
    string mapName;
    string scoresName;
    if(argc > 2){
      mapName = argv[1];
      scoresName = argv[2];
    }
    else{
      cout << "Some fils are missing. Exiting..." << endl;
      exit(1);
    }
    ifstream maze(mapName);
    if (!maze)
    {
        cout << "File failed to open." << endl;
        exit(1);
    }
    ifstream hiScores;
    hiScores.open(scoresName, ios::in | ios::binary);
    Engine gameEngine(maze, hiScores, scoresName);
    initscr();
    curs_set(0);
    noecho();
    gameEngine.startGame();
    refresh();
    endwin();
}
