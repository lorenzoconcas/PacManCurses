#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

/*BOOL*/
//A
bool allCollectibleEaten(point * collectibles, point * specialCollectibles);
bool isCollidingWithWall(point entity);
//i
int isGhostCollidingWithOthers(int ghost_id, point * ghosts_position); //è comunque un bool perchè consideriamo -1 come false
bool isInSpawn(point ghost);
bool isInCollisionAllowedArea(point ghost);
bool isSamePoint(point a, point b);


/*CHAR*/
char * getAudio(int audioFile);


/*INT*/
//C
int collectible_pointsSize();
int CountNotZero(int * array, int size);
//E
int eatenPoints(point * collectibles, int size);
//G
int getFreeDirection(point position);
int getOppositeDirection(int direction);;
//R
int rnd(int MAX, int MIN);


/*POINT*/

point  getCherryPoint();
point  GetGhostSpawnPoint(int id);
point* getMaze();
point  GetNextGhostSpawnPosition(point ghost);
point  getGhostSpawn2(int id);

/*VOID*/
//A
void audioProcess(int pipeIn, int pipeOut);
//C
void clearZone();
void clockProcess(int pipeOut);
//D
void defineColors();
void drawScene(point player_position, char player_icon, point* collectibles, point* special_collectibles, point* ghosts_position, bulletS * bullets, int bulletCounter, bool invert, int points, int lifes, point cherry);	
//I
void initScreen();
//G
void getFreeDirections(point position,  int freeDirections[4]);
void getGhostSpawn(point * array);
void getCollectibles(point * array);
void getNextPosition(point *ghost);
void getSpecialCollectibles(point * array);
//P
void printMaze();
void printPoints(point *, point *);
//R
void restoreEnvironment();
//S
void setGhostSpawn(point *ghost, int index);
void setupEnvironment();


/*Special functions*/
void logPoints(char * fName, point * array, int size);
void logNumber(char * fName, int i);
void logString(char * fName, char * string);
void logPoint(char * fName, point point);



#endif