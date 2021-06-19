#include "Engine.h"

void moveAndAddch(int i,int j,char ch){
  move(i,j);
  addch(ch);
}

//Engine Constructor
Engine::Engine(ifstream &myfile, ifstream &hiScores, string scoresFileName)
{
    this->marginX = 50;
    this->marginY = 10;
    this->mazeFile = &myfile;
    this->playerScore = 0;
    this->hiScore = new HiScore(scoresFileName);
    string line;
    if (hiScores){
      this->hiScore->readHiScores(hiScores);
    }
    else{
      this->hiScore->initHiScores();
    }
    hiScores.close();
    this->finalNotif = " ";
    this->wasEmeraldGnome = false;
    this->wasEmeraldTraal = false;
    this->fullExit = false;
  }

//Initializes the Vellum (This is used inside startGame after checking if the player has collected every gem)
void Engine::initVellum()
{
    int x, y;
    do
    {
        y = rand() % this->maze.size();
        x = rand() % this->maze[y].size();
    } while (maze[y][x] != ' ');
    maze[y][x] = 'V';
    moveAndAddch(marginY + y, marginX + x, 'V');
}

//Initializes gems to their first (and last) position
void Engine::initGems()
{
    int i, x, y;
    for (i = 1; i <= 10; i++)
    {
        do
        {
            y = rand() % this->maze.size();
            x = rand() % this->maze[y].size();
        } while (maze[y][x] != ' ');
        maze[y][x] = 'E';
    }
}

//Reads maze from the file and places it into a vector
void Engine::initMaze()
{
    this->hiScore->showHiScores(this->playerScore);
    int i, j;
    int x = this->marginX, y = this->marginY;
    string myText;
    while (getline(*this->mazeFile, myText))
    {
        vector<char> line;
        for (i = 0; i < myText.length(); i++)
        {
            line.push_back(myText.at(i));
        }
        this->maze.push_back(line);
    }
    this->initGems();
    this->initEntity(this->potter, 'P');
    this->initEntity(this->gnome, 'G');
    this->initEntity(this->traal, 'T');
    for (i = 0; i < this->maze.size(); i++)
    {
        move(y, x);
        for (j = 0; j < this->maze[i].size(); j++)
        {
          moveAndAddch(y, x,this->maze[i][j]);
          x++;
        }
        y++;
        x = marginX;
    }
}


//Initializes a sprcific entity
void Engine::initEntity(Moving &entity, char entitySymbol)
{
    do
    {
        entity.setPosY(rand() % this->maze.size());
        entity.setPosX(rand() % this->maze[entity.getPosY()].size());
    } while (this->maze[entity.getPosY()][entity.getPosX()] != ' ');
    this->maze[entity.getPosY()][entity.getPosX()] = entitySymbol;
}

//Starts the game
void Engine::startGame()
{
    initMaze();
    this->end = false;
    int input;
    keypad(stdscr, TRUE);
    do
    {
        do
        {
            input = getch();
        } while (this->potter.checkMove(input, maze, 'P') == false);
        if(input == 27){
          this->fullExit = true;
          this->end = true;

        }
        else{
          this->moveEntity(input,this->potter, 'P');
          this->calculateAndMoveEnemy(this->gnome, 'G');
          this->calculateAndMoveEnemy(this->traal, 'T');
          this->checkAndInitVellum();
        }
        this->hiScore->updatePlayerScore(this->playerScore);
    } while (this->end == false);
    if(!this->fullExit){
      this->updateHiScores();
      this->showEndScreen();
    }

}

//Updates High Scores Array
void Engine::updateHiScores(){
  this->getName();
  this->hiScore->updateHiScores(this->playerScore, this->playerName);

}

void Engine::getName(){
  clear();
  endwin();
  system("clear");
  cout << "What is your name?" << endl;
  cin >> this->playerName;
  while(this->playerName.length() > 10){
    cout << "Name too long, Try again." << endl;
    cin >> this-> playerName;
  }
}

//Creates the ending Screen.
void Engine::showEndScreen(){
  initscr();
  clear();
  this->hiScore->showHiScores(this->playerScore);
  char* charFinalNotif = (char*) this->finalNotif.c_str();

  for(int i = 0; i < strlen(charFinalNotif) + 4; i++){
    moveAndAddch(22, 50 + i, '*');
    moveAndAddch(26, 50 + i, '*');
  }
  for(int i = 0; i < 3; i++){
    moveAndAddch(23+i, 50, '*');
    moveAndAddch(23+i, strlen(charFinalNotif) + 53, '*');
    moveAndAddch(23+i, strlen(charFinalNotif) + 55, '*');
    moveAndAddch(23+i, strlen(charFinalNotif) + 75, '*');
  }
  move(24, 52);
  printw(charFinalNotif);
  move(22, strlen(charFinalNotif) + 55);
  printw("*********************");
  move(24, strlen(charFinalNotif) + 57);
  printw("YOUR SCORE IS ");
  stringstream strs;
  strs << playerScore;
  string stringPlayerScore = strs.str();
  char* charPlayerScore = (char*) stringPlayerScore.c_str();;
  printw(charPlayerScore);
  move(26, strlen(charFinalNotif) + 55);
  printw("*********************");
  getch();
}


//Moves a given Entity to a given direction
void Engine::moveEntity(int input, Moving &entity, char entitySymbol)
{

    move(this->marginY + entity.getPosY(), this->marginX + entity.getPosX());
    if((this->wasEmeraldGnome && entitySymbol == 'G')){
      this->maze[entity.getPosY()][entity.getPosX()] = 'E';
      addch('E');
      this->wasEmeraldGnome = false;
    }
    if(this->wasEmeraldTraal && entitySymbol == 'T'){
      this->maze[entity.getPosY()][entity.getPosX()] = 'E';
      addch('E');
      this->wasEmeraldTraal = false;
    }
    else{
      this->maze[entity.getPosY()][entity.getPosX()] = ' ';
      addch(' ');
    }
    switch (input)
    {
    case KEY_UP:
        entity.setPosY(entity.getPosY() - 1);
        break;
    case KEY_DOWN:
        entity.setPosY(entity.getPosY() + 1);
        break;
    case KEY_LEFT:
        entity.setPosX(entity.getPosX() - 1);
        break;
    case KEY_RIGHT:
        entity.setPosX(entity.getPosX() + 1);
        break;
    }
    if(entitySymbol == 'P'){
      if(this->maze[entity.getPosY()][entity.getPosX()] == 'T' || this->maze[entity.getPosY()][entity.getPosX()] == 'G'){
        this->finalNotif = "I AM SORRY YOU LOST! PRESS ANY KEY TO EXIT";
        this->end = true;

      }
      this->checkForGem();
      this->checkWin();
    }
    if(entitySymbol == 'G')
      if(this->maze[entity.getPosY()][entity.getPosX()] == 'E')
        this->wasEmeraldGnome = true;
      if(this->maze[entity.getPosY()][entity.getPosX()] == 'P'){
        this->finalNotif = "I AM SORRY YOU LOST! PRESS ANY KEY TO EXIT";
        this->end = true;
      }
    if(entitySymbol == 'T'){
      if(this->maze[entity.getPosY()][entity.getPosX()] == 'E'){
        this->wasEmeraldTraal = true;
      }
      if(this->maze[entity.getPosY()][entity.getPosX()] == 'P'){
        this->finalNotif = "I AM SORRY YOU LOST! PRESS ANY KEY TO EXIT";
        this->end = true;
      }
    }
    this->maze[entity.getPosY()][entity.getPosX()] = entitySymbol;
    moveAndAddch(this->marginY + entity.getPosY(), this->marginX + entity.getPosX(), entitySymbol);

}

void Engine::checkForGem()
{
    if (maze[this->potter.getPosY()][this->potter.getPosX()] == 'E'){
      this->potter.setGems(this->potter.getGems() + 1);
      this->playerScore+=10;
    }

}

void Engine::checkAndInitVellum()
{
    if (this->potter.getGems() == 10)
    {
        this->initVellum();
        this->potter.setGems(0);
    }
}

void Engine::checkWin(){
  if(maze[this->potter.getPosY()][this->potter.getPosX()] == 'V'){
    this->playerScore += 50;
    this->finalNotif = "YOU WON!!! PRESS ANY KEY TO EXIT";
    this->end = true;
  }
}

void Engine::calculateAndMoveEnemy(Moving &enemy, char enemySymbol){

    //PLAYER IS ABOVE AND TO THE LEFT OF YOU
  if(this->potter.getPosY() <= enemy.getPosY() && this->potter.getPosX() <= enemy.getPosX())
    //If the player is further away from you on the Y axis than on the X axis,
    if((enemy.getPosY() - this->potter.getPosY() >= enemy.getPosX() - this->potter.getPosX()))
      //And you can move up,
      if(enemy.checkMove(KEY_UP, this->maze, enemySymbol))
        //move up.
        moveEntity(KEY_UP, enemy, enemySymbol);
      //If you can't move up,
      else
        //And you can move left,
        if( enemy.checkMove(KEY_LEFT, this->maze, enemySymbol))
          //move left.
          moveEntity(KEY_LEFT, enemy, enemySymbol);
        //If you can't move left, stay still(Hope you will move soon xD).
        else
          moveEntity(' ', enemy, enemySymbol);
    //If the player is further away from you on the X axis than on the Y axis,
    else
      //And you can move left,
      if(enemy.checkMove(KEY_LEFT, this->maze, enemySymbol))
        //move left.
        moveEntity(KEY_LEFT, enemy, enemySymbol);
      //If you can't move left,
      else
        //And you can move up,
        if( enemy.checkMove(KEY_UP, this->maze, enemySymbol))
          //move up.
          moveEntity(KEY_UP, enemy, enemySymbol);
        //If you can't move up, stay still(Hope you will move soon xD).
        else
          moveEntity(' ', enemy, enemySymbol);
  //PLAYER IS ABOVE AND TO THE RIGHT OF YOU
  else if(this->potter.getPosY() <= enemy.getPosY() && this->potter.getPosX() >= enemy.getPosX())
    //If the player is further away from you on the Y axis than on the X axis,
    if((enemy.getPosY() - this->potter.getPosY() >= this->potter.getPosX() - enemy.getPosX()))
      //And you can move up,
      if(enemy.checkMove(KEY_UP, this->maze, enemySymbol))
        //move up.
        moveEntity(KEY_UP, enemy, enemySymbol);
      //If you can't move up,
      else
        //And you can move right,
        if( enemy.checkMove(KEY_RIGHT, this->maze, enemySymbol))
          //move right.
          moveEntity(KEY_RIGHT, enemy, enemySymbol);
        //If you can't move right, stay still(Hope you will move soon xD).
        else
        moveEntity(' ', enemy, enemySymbol);
    //If the player is further away from you on the X axis than on the Y axis,
    else
      //And you can move right,
      if(enemy.checkMove(KEY_RIGHT, this->maze, enemySymbol))
        //move right.
        moveEntity(KEY_RIGHT, enemy, enemySymbol);
      //If you can't move right,
      else
        //And you can move up,
        if( enemy.checkMove(KEY_UP, this->maze, enemySymbol))
          //move up.
          moveEntity(KEY_UP, enemy, enemySymbol);
        //If you can't move up, stay still(Hope you will move soon xD).
        else
        moveEntity(' ', enemy, enemySymbol);
  //PLAYER IS UNDERNEATH AND TO THE LEFT OF YOU
  else if(this->potter.getPosY() >= enemy.getPosY() && this->potter.getPosX() <= enemy.getPosX())
    //If the player is further away from you on the Y axis than on the X axis,
    if((this->potter.getPosY() - enemy.getPosY() >= enemy.getPosX() - this->potter.getPosX()))
      //And you can move down,
      if(enemy.checkMove(KEY_DOWN, this->maze, enemySymbol))
        //move down.
        moveEntity(KEY_DOWN, enemy, enemySymbol);
      //If you can't move down,
      else
        //And you can move left,
        if( enemy.checkMove(KEY_LEFT, this->maze, enemySymbol))
          //move left.
          moveEntity(KEY_LEFT, enemy, enemySymbol);
        //If you can't move left, stay still(Hope you will move soon xD).
        else
        moveEntity(' ', enemy, enemySymbol);
    //If the player is further away from you on the X axis than on the Y axis,
    else
      //And you can move left,
      if(enemy.checkMove(KEY_LEFT, this->maze, enemySymbol))
        //move left.
        moveEntity(KEY_LEFT, enemy, enemySymbol);
      //If you can't move left,
      else
        //And you can move down,
        if( enemy.checkMove(KEY_DOWN, this->maze, enemySymbol))
          //move down.
          moveEntity(KEY_DOWN, enemy, enemySymbol);
        //If you can't move down, stay still(Hope you will move soon xD).
        else
          moveEntity(' ', enemy, enemySymbol);

  //PLAYER IS UNDERNEATH AND TO THE RIGHT OF YOU
  else if(this->potter.getPosY() >= enemy.getPosY() && this->potter.getPosX() >= enemy.getPosX())
    //If the player is further away from you on the Y axis than on the X axis,
    if((this->potter.getPosY() - enemy.getPosY() >= enemy.getPosX() - this->potter.getPosX()))
      //And you can move down,
      if(enemy.checkMove(KEY_DOWN, this->maze, enemySymbol))
        //move down.
          moveEntity(KEY_DOWN, enemy, enemySymbol);
      //If you can't move down,
      else
        //And you can move right,
        if( enemy.checkMove(KEY_RIGHT, this->maze, enemySymbol))
          //move right.
          moveEntity(KEY_RIGHT, enemy, enemySymbol);
        //If you can't move right, stay still(Hope you will move soon xD).
        else
          moveEntity(' ', enemy, enemySymbol);
    //If the player is further away from you on the X axis than on the Y axis,
    else
      //And you can move right,
      if(enemy.checkMove(KEY_RIGHT, this->maze, enemySymbol))
        //move right.
        moveEntity(KEY_RIGHT, enemy, enemySymbol);
      //If you can't move right,
      else
        //And you can move down,
        if( enemy.checkMove(KEY_DOWN, this->maze, enemySymbol))
          //move down.
          moveEntity(KEY_DOWN, enemy, enemySymbol);
        //If you can't move down, stay still(Hope you will move soon xD).
        else
        moveEntity(' ', enemy, enemySymbol);
}
