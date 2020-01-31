#include "libs.h"

const point walls[] = {
	{0,0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}, {8, 0}, {9, 0}, {10, 0}, {11, 0}, {12, 0}, {13, 0}, {14, 0}, {15, 0}, {16, 0}, {17, 0}, {18, 0}, //bordo alto 
	{0, 20}, {1, 20}, {2, 20}, {3, 20}, {4, 20}, {5, 20}, {6, 20}, {7, 20}, {8, 20}, {9, 20}, {10, 20}, {11, 20}, {12, 20}, {13, 20}, {14, 20}, {15, 20}, {16, 20}, {17, 20}, {18, 20}, //bordo basso
	{0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {0, 8}, {0, 10},  {0, 12}, {0, 13}, {0, 14}, {0, 15}, {0, 16}, {0, 17}, {0, 18}, {0, 19}, //bordo sx
	{18, 1}, {18, 2}, {18, 3}, {18, 4}, {18, 5}, {18, 6},  {18, 8},  {18, 10}, {18, 12}, {18, 13}, {18, 14}, {18, 15}, {18, 16}, {18, 17}, {18, 18}, {18, 19}, //bordo dx

	//mura interne
	{9, 1}, {9,2},
	{2,2}, {3,2}, {5,2}, {6,2}, {7,2},  {11,2}, {12,2}, {13,2}, {15,2}, {16,2},
	{2,4}, {3,4}, {5,4}, {7,4}, {8,4}, {9,4}, {10,4}, {11,4}, {13,4}, {15,4}, {16,4},
	{5,5}, {9,5}, {13,5},
	{1,6}, {2,6}, {3,6}, {5,6}, {6,6}, {7,6}, {9,6}, {11,6}, {12,6}, {13,6}, {15,6}, {16,6}, {17,6},
	{3,7}, {5,7}, {13,7}, {15, 7},
	{1,8}, {2,8}, {3,8}, {5,8},  {7,8}, {8,8}, {10, 8}, {11,8},  {13,8}, {15,8}, {16,8}, {17,8},
	{7, 9}, {11, 9},
	{1,10}, {2,10}, {3,10}, {5,10},  {7,10}, {8,10},{9, 10}, {10, 10}, {11,10},  {13,10}, {15,10}, {16,10}, {17,10},
	{3,11}, {5,11}, {13,11}, {15, 11},
	{1,12}, {2,12}, {3,12}, {5,12},  {7,12}, {8,12}, {9, 12},{10, 12}, {11,12},  {13,12}, {15,12}, {16,12}, {17,12},
	{9, 13},
	{2,14}, {3,14}, {5,14}, {6,14},  {7,14}, {9, 14}, {11,14}, {12,14},  {13,14}, {15,14}, {16,14},
	{3, 15}, {15, 15},
	{1, 16}, {3, 16}, {5, 16}, {7, 16}, {8, 16}, {9, 16}, {10, 16}, {11, 16}, {13, 16}, {15, 16}, {17, 16},
	{5, 17}, {9, 17},{13, 17},
	{2, 18}, {3, 18},{4, 18}, {5, 18}, {6, 18}, {7, 18}, {9, 18}, {11, 18}, {12, 18}, {13, 18},{14, 18}, {15, 18}, {16, 18}
};

const point collectible_points[]={  
	{1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1}, {6, 1}, {7, 1}, {8, 1}, {10, 1}, {11, 1}, {12, 1}, {13, 1}, {14, 1}, {15, 1}, {16, 1}, {17, 1}, 
	{1, 2}, {4, 2}, {8, 2}, {10, 2}, {14, 2}, {17, 2}, 
	{1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}, {6, 3}, {7, 3}, {8, 3}, {9, 3}, {10, 3}, {11, 3}, {12, 3}, {13, 3}, {14, 3}, {15, 3}, {16, 3}, {17, 3}, 
	{1, 4}, {4, 4}, {6, 4}, {12, 4}, {14, 4}, {17, 4}, 
	{1, 5}, {2, 5}, {3, 5}, {4, 5}, {6, 5}, {7, 5}, {8, 5}, {10, 5}, {11, 5}, {12, 5}, {14, 5}, {15, 5}, {16, 5}, {17, 5},
	{4, 6}, {8, 6}, {10, 6}, {14, 6}, 
	{4, 7}, {6, 7}, {7, 7}, {8, 7}, {9, 7}, {10, 7}, {11, 7}, {12, 7}, {14, 7}, 
	{4, 8}, {6, 8}, {9, 8}, {12, 8}, {14, 8},  
	{0, 9}, {1, 9}, {2, 9}, {3, 9}, {4, 9 }, {5, 9}, {6, 9}, {8, 9}, {9, 9}, {10, 9}, {12, 9}, {13, 9}, {14, 9}, {15, 9}, {16, 9}, {17, 9}, {18,9},
	{4, 10}, {6, 10}, {12, 10}, {14, 10},
	{4, 11}, {6, 11}, {7, 11}, {8, 11}, {9, 11}, {10, 11}, {11, 11}, {12, 11}, {14, 11}, 
	{4, 12}, {6, 12}, {12, 12}, {14, 12}, 
	{1, 13}, {2, 13}, {3, 13}, {4, 13}, {5, 13}, {6, 13}, {7, 13}, {8, 13}, {10, 13}, {11, 13}, {12, 13}, {13, 13}, {14, 13}, {15, 13}, {16, 13}, {17, 13}, 
	{1, 14}, {4, 14}, {8, 14}, {10, 14}, {14, 14}, {17, 14}, 
	{1, 15}, {2, 15}, {4, 15}, {5, 15}, {6, 15}, {7, 15}, {8, 15}, {9, 15}, {10, 15}, {11, 15}, {12, 15}, {13, 15}, {14, 15}, {16, 15}, {17, 15}, 
	{2, 16}, {4, 16}, {6, 16}, {12, 16}, {14, 16}, {16, 16}, 
	{1, 17}, {2, 17}, {3, 17}, {4, 17}, {6, 17}, {7, 17}, {8, 17}, {10, 17}, {11, 17}, {12, 17}, {14, 17}, {15, 17}, {16, 17}, {17, 17}, 
	{1, 18}, {8, 18}, {10, 18}, {17, 18},
	{1, 19}, {2, 19}, {3, 19}, {4, 19}, {5, 19}, {6, 19}, {7, 19}, {8, 19}, {9, 19}, {10, 19}, {11, 19}, {12, 19}, {13, 19}, {14, 19}, {15, 19}, {16, 19}, {17, 19},
};

const point collectible_points_specials[] ={
	{1, 3}, {17, 3}, {1, 15}, {17, 15}
};

int collectible_pointsSize(){
	return size(collectible_points);
}

void getCollectibles(point * array){
	int i = 0;
	for(i = 0; i < size(collectible_points); i++){
		array[i].x = collectible_points[i].x;
		array[i].y = collectible_points[i].y;
	}
}
void getSpecialCollectibles(point * array){
	for(int i = 0; i < size(collectible_points_specials); i++){
		array[i].x = collectible_points_specials[i].x;
		array[i].y = collectible_points_specials[i].y;
	}
}
void getGhostSpawn(point * array){
	array[0].x =  8;	array[0].y = 9;
	array[1].x =  9;	array[1].y = 9;
	array[2].x = 10;	array[2].y = 9;
	array[3].x =  9;	array[3].y = 8;	
}
point getGhostSpawn2(int id){
	point array[4];
	array[0].x =  8;	array[0].y = 9;
	array[1].x =  9;	array[1].y = 9;
	array[2].x = 10;	array[2].y = 9;
	array[3].x =  9;	array[3].y = 8;	

	return array[id];
}
void setGhostSpawn(point *ghost, int index){
	point ghostInitialPosition[GHOSTS];
	getGhostSpawn(ghostInitialPosition);
	ghost->x = ghostInitialPosition[index].x;
	ghost->y = ghostInitialPosition[index].y;
}
void getNextPosition(point *ghost){
	int x = ghost->x;
	int y = ghost->y;
	if(x == 9 && y == 8){
		ghost->y--;
		return;
	}
	/*if(x == 9 && y == 7){
		ghost->x++;
		return;
	}*/
	if(x == 8 && y == 9){
		ghost->x++;
		return;
	}
	if(x == 10 && y == 9){
		ghost->x--;
		return;
	}
	if(x == 9 && y == 9){
		ghost->y--;
		return;
	}
}
point GetNextGhostSpawnPosition(point ghost){
	int x = ghost.x;
	int y = ghost.y;
	if(x == 9 && y == 8){
		ghost.y--;
		return ghost;
	}
	
	if(x == 8 && y == 9){
		ghost.x++;		
		return ghost;
	}
	if(x == 10 && y == 9){
		ghost.x--;
		return ghost;
	}
	if(x == 9 && y == 9){
		ghost.y--;
		return ghost;
	}
	return ghost; //siamo già oltre lo spawn
}
point GetGhostSpawnPoint(int ghost_id){
	point p;
	switch(ghost_id){
		case 0 : p.x = 8; p.y = 9; break;
		case 1 : p.x = 9; p.y = 9; break;
		case 2 : p.x = 10; p.y = 9; break;
		case 3 : p.x = 9; p.y = 8; break;
	}
	return p;
}
bool isInSpawn(point ghost){
	int x = ghost.x;
	int y = ghost.y;
	if((x > 7 && x < 11) && (y >= 8 && y <= 10)){
		return true;
	}
	return false;
}

char * getAudio(int audioFile){
	/*const    char audio_files[][24] = {
		"pacman_beginning.wav", 
		"pacman_chomp.wav", 
		"pacman_death.wav", 
		"pacman_eatfruit.wav",
		 "pacman_eatghost.wav",
		  "pacman_extrapac.wav",
		   "pacman_intermission.wav"
	};*/

	//alcuni casi prevedono un delay pari alla durata del suono, li chiamiamo direttamente se scrivere messaggi nel buffere, in modo da bloccare l'esecuzione
	

	switch(audioFile){
		case EAT:			return "paplay pacman_chomp.wav 2> /dev/null &";
		case GHOST_EAT: 	return "paplay pacman_eatghost.wav 2> /dev/null &";
		case DEATH:			return "paplay pacman_death.wav 2> /dev/null";
		case BEGIN:			return "paplay pacman_beginning.wav 2> /dev/null";
		case FRUIT:			return "paplay pacman_eatfruit.wav 2> /dev/null";
		case NEW_LIFE:		return "paplay pacman_extrapac.wav 2> /dev/null";	
		default : return "";
	}
}

void printMaze(){
	attron(COLOR_PAIR(BLUE));
	int m_count = size(walls);
	for(int i = 0; i < m_count; i++){
		mvaddch(walls[i].y+HALF_HEIGHT, walls[i].x+HALF_WIDTH, WALL);
	}
	attroff(COLOR_PAIR(BLUE));
}
bool isCollidingWithWall(point entity){
	for(int i = 0; i<size(walls); i++){		
		if(entity.y == walls[i].y && entity.x == walls[i].x){
			return true;
		}
	}
	
	return false;
}
void printPoints(point * c_points, point * c_points_specials){
	attron(COLOR_PAIR(WHITE));
	
	for(int i = 0; i< size(collectible_points); i++){
		if(c_points[i].x != -1)
			mvaddch(c_points[i].y+HALF_HEIGHT, c_points[i].x+HALF_WIDTH, POINT);	
	}
	for(int i = 0; i<size(collectible_points_specials); i++){
		if(c_points_specials[i].x != -1)
			mvaddch(c_points_specials[i].y+HALF_HEIGHT, c_points_specials[i].x+HALF_WIDTH, POWER_POINT);	
	}
	attroff(COLOR_PAIR(WHITE));
}

bool allCollectibleEaten(point * collectibles, point * specialCollectibles){
	int normal = 0, special = 0;
	for(int i = 0; i < size(collectible_points); i++){
		if(collectibles[i].x != -1 && collectibles[i].y != -1)
			normal++;
	}

	for(int i = 0; i < SPECIAL_POINTS; i++){
		if(specialCollectibles[i].x != -1 && specialCollectibles[i].y != -1)
			special++;
	}
	return normal == size(collectibles) && special == SPECIAL_POINTS;
}
void initScreen(){
	initscr();
	noecho();
	curs_set(0);
	keypad(stdscr, true);
	start_color();
	defineColors();
	clearZone(S_WIDTH, S_HEIGHT);
}

void clearZone(int endX, int endY) {
	for (int y = 0; y < endY; y++) {
		for (int x = 0; x < endX; x++) {
			mvaddch(y, x, ' ');
		}
	}
}
void defineColors() {
	//definisce le coppie di colori
	if (has_colors()) {
		init_pair(0, COLOR_WHITE, COLOR_BLACK);
		init_pair(1, COLOR_BLACK, COLOR_WHITE);
		init_pair(2, COLOR_BLUE, COLOR_BLACK);
		init_pair(3, COLOR_YELLOW, COLOR_BLACK);
		init_pair(4, COLOR_RED, COLOR_BLACK);
		init_pair(5, COLOR_GREEN, COLOR_BLACK);
	}
}

void logPoints(char * fName, point * array, int size) {
	FILE * fp = NULL;
	fp = fopen(fName, "a");


	for(int i = 0; i< size; i++){
		fprintf(fp, "{%d, %d}\n", array[i].x, array[i].y);

	}
	fclose(fp);
}
void logPoint(char * fName, point point) {
	FILE * fp = NULL;
	fp = fopen(fName, "a");
	fprintf(fp, "{%d, %d}", point.x, point.y);	
	fclose(fp);
}

void logNumber(char * fName, int i) {
	FILE * fp = NULL;
	fp = fopen(fName, "a");
	fprintf(fp, "%d", i);
	fclose(fp);
}

void logString(char * fName, char * string) {
	FILE * fp = NULL;
	fp = fopen(fName, "a");

	fprintf(fp, "%s", string);
	fclose(fp);
}

int rnd(int MIN, int MAX){
	return MIN + rand() % (MAX - MIN + 1);
}


int getFreeDirection (point position){
	
	/*
	* questa funzione viene chiamata quando il fantasma è rimbalzato su un muro
	* dobbiamo trovare quale delle posizioni possibile non è un muro
	*/
	point candidate_positions[4];
	int freeDirections[3] = {0,0,0}; //questo ci servirà per scegliere una direzione casuale e non sottostare all'ordine dell'enum "direction"
	for(int i = 0; i<4; i++){
		candidate_positions[i] = position;
		//riusiamo un po' di codice collaudato, per non fare manualmente le assegnazioni
		switch(i+1){ //+1 perchè la prima posizione è STADY e i parte da 0
			case LEFT:	{ 	candidate_positions[i].x--; break;}
			case RIGHT:	{	candidate_positions[i].x++; break;}
			case UP:	{   candidate_positions[i].y--; break;}
			case DOWN:	{  	candidate_positions[i].y++; break;}
		}		
	}
	//ora cerchiamo nelle mura (TO-DO aggiungere controllo sulle mura esterne)
	//dobbiamo trovare quale point non esiste in quella lista

	int i = 0, k = 0, j = 0;
	for(i = 0; i < 4 ; i++){
		for(k = 0; k < size(walls); k++){
			//se troviamo che la direzione analizzata contiene un muro passiamo a quella successiva
			if(candidate_positions[i].x == walls[k].x && candidate_positions[i].y == walls[k].y){
				break;
			}
		}
		if(k == size(walls)){
			if(freeDirections[j] != 0)
				j++;
			freeDirections[j]= i+1;			
		}		
	}

	int rndnumber = rnd(0, j);
	
		
	int result = freeDirections[rndnumber];
	
	return result;
}

void getFreeDirections(point position, int freeDirections[4]){

	point candidate_positions[4];
	//freeDirections = {0,0,0,0}; //questo ci servirà per scegliere una direzione casuale e non sottostare all'ordine dell'enum "direction"
	
	for(int i = 0; i<4; i++){
		candidate_positions[i] = position;
		//riusiamo un po' di codice collaudato, per non fare manualmente le assegnazioni
		switch(i+1){ //+1 perchè la prima posizione è STADY e i parte da 0
			case LEFT:	{ 	candidate_positions[i].x--; break;}
			case RIGHT:	{	candidate_positions[i].x++; break;}
			case UP:	{   candidate_positions[i].y--; break;}
			case DOWN:	{  	candidate_positions[i].y++; break;}
		}		
	}
	//ora cerchiamo nelle mura (TO-DO aggiungere controllo sulle mura esterne)
	//dobbiamo trovare quale point non esiste in quella lista

	int i = 0, k = 0, j = 0;

	int wallCount = size(walls);


	for(i = 0; i < 4 ; i++){
		for(k = 0; k < wallCount; k++){
			//se troviamo che la direzione analizzata contiene un muro passiamo a quella successiva
			if(candidate_positions[i].x == walls[k].x && candidate_positions[i].y == walls[k].y){
				break;
			}
		}
		if(k == wallCount){
			if(freeDirections[j] != 0)
				j++;
			freeDirections[j]= i+1;			
		}		
	}	
}
int CountNotZero(int * array, int size){
	int count = 0;
	for(int i = 0; i< size; i++){
		if(array[i] != 0)
			count++;
	}
	
	return count;
}
int getOppositeDirection(int direction){
	switch(direction){
		case UP: return DOWN;
		case DOWN: return UP;
		case LEFT: return RIGHT;
		case RIGHT: return LEFT;
	}
	return STADY;
}

void drawScene(point player_position, char player_icon, point* collectibles, point* special_collectibles, point* ghosts_position, bulletS * bullets, int bulletCounter, bool invert, int points, int lifes, point cherry){
	clearScreen();

	//stampiamo i muri
	printMaze();
	//stampo i collectible in modo easy, quelli disattivati stanno a -1,-1, quelli che spawnano i fantasmi a -x, -y

	printPoints(collectibles, special_collectibles);



	//To-DO Implementare i fantasmini blu
	//lo si fa con un check della pos
	//stampa i fantsmini in ordine
	for(int i = 0; i<GHOSTS; i++){
		//mvprintw(i, 0, "Ghost %d {%d, %d}, cArea %d", i, ghosts_position[i].x, ghosts_position[i].y, isInCollisionAllowedArea(ghosts_position[i]));
		if(invert)
			attron(COLOR_PAIR(BLUE));
		else
			attron(COLOR_PAIR(BLUE+i));
		if(ghosts_position[i].x != -1)
			mvaddch(HALF_HEIGHT+ghosts_position[i].y, HALF_WIDTH+ghosts_position[i].x, GHOST);

		if(invert)
			attroff(COLOR_PAIR(BLUE));
		else
			attroff(COLOR_PAIR(BLUE+i));
	}


	for(int i = 0; i<bulletCounter; i++)
		if(bullets[i].position.x > 0)		
			mvaddch(bullets[i].position.y+HALF_HEIGHT, bullets[i].position.x+HALF_WIDTH, '<');

	   
	//questo è il player
	attron(COLOR_PAIR(YELLOW));
	mvaddch(player_position.y+HALF_HEIGHT, player_position.x+HALF_WIDTH, player_icon);
	attroff(COLOR_PAIR(YELLOW));

	mvprintw(22+HALF_HEIGHT, HALF_WIDTH, "POINTS %d", points);

	//stampa le icone delle vite
	attron(COLOR_PAIR(YELLOW));
	for(int i = 0; i < lifes; i++){
		mvaddch(21+HALF_HEIGHT, HALF_WIDTH+i, PAC_LIFE);
	}
	attroff(COLOR_PAIR(YELLOW));

	attron(COLOR_PAIR(RED));
	if(cherry.x > 0)
		mvaddch(cherry.y+HALF_HEIGHT, cherry.x+HALF_WIDTH, CHERRY);
	attroff(COLOR_PAIR(RED));
	

	refresh();	
}


void clockProcess(int pipeOut){
	message msg;
	msg.sender = CLOCK_PROCESS;
	msg.value = 0;
	while(true){
		write(pipeOut, &msg, sizeof(message));
		msg.value++;
		usleep(SECOND); 
	}
}
void audioProcess(int pipeIn, int pipeOut){

	message msg;
	
	while(true){
		read(pipeIn, &msg, sizeof(message));
		if(msg.sender != MAIN_PROCESS){			
			write(pipeOut, &msg, sizeof(message));
		}else{		
			system(getAudio(msg.value));		
		}
	}
}

int isGhostCollidingWithOthers(int ghost_id, point * ghosts_position){
	
	for(int i = 0; i < 4; i++){
		if(i != ghost_id){
			if(ghosts_position[ghost_id].x == ghosts_position[i].x && ghosts_position[ghost_id].y == ghosts_position[i].y){
				return i;
			}
		}
	}
	return -1;
}

bool isInCollisionAllowedArea(point ghost){
	return ((ghost.x >= 5 && ghost.x <= 13) && (ghost.y >= 4 && ghost.y <= 8));
}


bool isSamePoint(point a, point b){
	return (a.x == b.x) && (a.y == b.y);
}

point getCherryPoint(){
	int i = rnd(0, NORMAL_POINTS);
	return collectible_points[i];
}
int eatenPoints(point * collectibles, int size){
	int eat = 0;
	for(int i = 0; i < size; i++){
		if(collectibles[i].x < 0 && collectibles[i].y < 0)
			eat++;
	}
	return eat;
}

void logMessage(char * fName, message msg){

	char *dirNames[6] = {"STADY", "LEFT", "RIGHT","UP","DOWN", "DEAD"};
char *processNames[14] = {"PLAYER_PROCESS", "GHOST_PROCESS", "MAIN_PROCESS", "CLOCK_PROCESS", "AUDIO_PROCESS", "BULLET_PROCESS"};

	FILE * fp = NULL;

	fp = fopen(fName, "a");

	//fprintf(fp, "SNDR RCVR  VL   POS S ID\n");
	if(msg.id == 0)
		fprintf(fp, "\n");
	fprintf(fp, "%s", processNames[msg.sender]);
	fprintf(fp, "   %s", processNames[msg.receiver]);
	fprintf(fp, "  %s", dirNames[msg.value]);
	fprintf(fp, "  {%d,%d}", msg.position.x, msg.position.y);
	fprintf(fp, " Shoot : %d", msg.shoot);
	fprintf(fp, " ID : %d", msg.id);

	fprintf(fp, "\n");
	fclose(fp);
}

