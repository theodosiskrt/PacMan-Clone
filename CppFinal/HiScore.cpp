#include "HiScore.h"

void moveAndPrintw(int i,int j,string text){
  move(i,j);
  char *charText = (char *) text.c_str();
  printw(charText);
}

string HiScore::getHighScore(int index1, int index2){ return this->hiScores[index1][index2]; }

HiScore::HiScore(string scoresFileName){
  this->leftBorder = 4;
  this->rightBorder = 38;
  this->topBorder = 10;
  this->bottomBorder = 44;
  this->middleBorder = (this->bottomBorder + this->topBorder)/2;
  this->scoresFileName = scoresFileName;
}

void HiScore::showHiScores(int playerScore){
  for (int i = this->leftBorder; i <= this->rightBorder; i++){
    move(this->topBorder,i);
    addch('*');
    move(this->bottomBorder, i);
    addch('*');
    move(this->middleBorder, i);
    addch('*');
  }
  for(int i = this->topBorder + 1; i <= this->bottomBorder - 1; i++){
    move(i,this->leftBorder);
    addch('*');
    move(i,this->rightBorder);
    addch('*');
  }
  moveAndPrintw(this->topBorder + 2, this->leftBorder + 11, "HIGHSCORES:");
  for(int i = 0; i < 5; i++){
    move(i*2 + this->topBorder + 4, this->leftBorder + 11);
    char* charScore = (char*) this->hiScores[i][0].c_str();;
    printw(charScore);
    addch(' ');
    charScore = (char*) this->hiScores[i][1].c_str();;
    printw(charScore);
  }
  moveAndPrintw(this->middleBorder - 3, this->leftBorder + 11, "YOUR SCORE:");
  move(this->middleBorder - 2, this->leftBorder + 11);
  stringstream strs;
  strs << playerScore;
  string stringPlayerScore = strs.str();
  char* charPlayerScore = (char*) stringPlayerScore.c_str();
  printw(charPlayerScore);
  moveAndPrintw(middleBorder + 2, this->leftBorder + 8, "INSTRUCTIONS:");
  moveAndPrintw(middleBorder + 4, this->leftBorder + 8,"Movement: Arrow Keys");
  moveAndPrintw(middleBorder + 5, this->leftBorder + 8, "Stay Still: Space");
  moveAndPrintw(middleBorder + 6, this->leftBorder + 8, "Exit: Esc (Escape)");
  moveAndPrintw(middleBorder + 8, this->leftBorder + 2, "Your goal is to collect every");
  moveAndPrintw(middleBorder + 9, this->leftBorder + 2, "Emerald (E) and avoid your");
  moveAndPrintw(middleBorder + 10, this->leftBorder + 2, "Enemies (G, T). The game is ");
  moveAndPrintw(middleBorder + 11, this->leftBorder + 2, "played in rounds, so your ");
  moveAndPrintw(middleBorder + 12, this->leftBorder + 2, "enemies will move only if you ");
  moveAndPrintw(middleBorder + 13, this->leftBorder + 2, "move. When you collect every ");
  moveAndPrintw(middleBorder + 14, this->leftBorder + 2, "Emerald, a Vellum will appear.");
  moveAndPrintw(middleBorder + 15, this->leftBorder + 2, "Collect it and the win is yours.");
}

void HiScore::updatePlayerScore(int playerScore){
  move(this->middleBorder - 2, this->leftBorder + 11);
  stringstream strs;
  strs << playerScore;
  string stringPlayerScore = strs.str();
  char* charPlayerScore = (char*) stringPlayerScore.c_str();
  printw(charPlayerScore);
}


void HiScore::setHighScore(int index1, int index2, string input){
  this->hiScores[index1][index2] = input;
}

void HiScore::readHiScores(ifstream &hiScores){
  for(int i = 0; i < 5; i++){
    for( int j = 0; j < 2; j++){
      string line;
      if(getline(hiScores,line))
        this->hiScores[i][j] = line;
      else{
        if(j == 0)
          this->hiScores[i][j] = "0";
        else
          this->hiScores[i][j] = "No-one";
      }
    }
  }
}

void HiScore::initHiScores(){
  for(int i = 0; i < 5; i++)
    for( int j = 0; j < 2; j++)
      if(j == 0){
        this->hiScores[i][j] = "0";
      }
      else{
        this->hiScores[i][j] = "No-one";
      }
}

void HiScore::updateHiScores(int playerScore, string playerName){
  int i;
  for(i = 5; i > 0; i--){
    if(playerScore > stoi(this->hiScores[i - 1][0])){
      string temp = this->hiScores[i-1][0];
      this->hiScores[i-1][0] = to_string(playerScore);
      if(i < 5)
        this->hiScores[i][0] = temp;
      temp = this->hiScores[i-1][1];
      this->hiScores[i-1][1] = playerName;
      if(i < 5)
        this->hiScores[i][1] = temp;

    }
    else{
      break;
    }
  }
  ofstream hiScores;
  hiScores.open(this->scoresFileName, ios::out | ios::binary);
  for(int i = 0; i < 5; i++){
    hiScores << this->hiScores[i][0] << endl;
    hiScores << this->hiScores[i][1] << endl;
  }
  hiScores.close();
}
