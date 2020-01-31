#ifndef DEFINITIONS_H_INCLUDED
#define DEFINITIONS_H_INCLUDED

#define DEBUG 0


#define MAZE_HEIGHT 21
#define PAC_LEFT 	'{'
#define PAC_RIGHT 	'}'
#define PAC_LIFE 	'@'
#define GHOST 		'|'
#define WALL 		'#'
#define POINT 		'*'
#define POWER_POINT '+'
#define CHERRY 		'~'
#define EMPTY		' '

//colors
#define WHITE	0
#define BLACK	1
#define BLUE	2
#define YELLOW	3
#define RED		4
#define GREEN	5
#define NONE   -1

#define S_WIDTH 	getmaxx(stdscr)
#define S_HEIGHT 	getmaxy(stdscr)
#define HALF_WIDTH 	(S_WIDTH - 19)/2
#define HALF_HEIGHT (S_HEIGHT -20)/2

#define clearScreen() clearZone(S_WIDTH, S_HEIGHT)

#define size(x) 	(signed int)(sizeof(x) / sizeof((x)[0])) //!!! usare solo su array già definiti e non passati tramite puntatori

#define PROCESS_COUNT		4
#define GHOSTS				4
#define SPECIAL_POINTS      4
#define NORMAL_POINTS       189
#define INTERNAL_WALLS 		128
#define DELAY  				100000
#define GHOST_DELAY 		SECOND / 4
#define PLAYER_DELAY 		GHOST_DELAY * 4 + GHOST_DELAY
#define GHOST_CACHE_SIZE    GHOST*5
#define SECOND 				1000000
#define POINT_VALUE 		10
#define SPECIAL_POINT_VALUE 50
#define RANDOM_SHOT_PROBABILITY 500 //significa che c'è 1 probabilità su {VALORE} che il fantasma spari
#define CHERRY_PROBABILITY 50
#define GHOST_SPAWN_PROBABILITY 10
#define ESCAPE ''

#define tuple point

#define suicide kill(getpid(), SIGKILL)
#define resetPlayer player_position.x =9; player_position.y = 15

#endif
