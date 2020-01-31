#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED


typedef struct{
	int x;
	int y;
}point;

			//  0      1     2    3    4     5
typedef enum {STADY, LEFT, RIGHT,UP,  DOWN, DEAD} direction;
typedef enum {WIN, LOST, GIVEUP} game_result;
typedef enum {PLAYER_PROCESS, GHOST_PROCESS, MAIN_PROCESS, CLOCK_PROCESS, AUDIO_PROCESS, BULLET_PROCESS} process_id;
typedef enum {BEGIN, EAT, CAPTURED, SPECIAL_EAT, BONUS, DEATH, GHOST_EAT, FRUIT, NEW_LIFE} audio_action;

typedef struct{	
	int sender;
	int receiver;
	int value;
	point position;
	bool shoot;
	int id;
}message;

typedef struct{
	point position;
	int target;
}bulletS;

#endif // STRUCT_H_INCLUDED
