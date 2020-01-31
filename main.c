#include "libs.h"

int main(){
	int p[2]; //pipe di comunicazione dei processi p[0] pipeIn, p[1] pipeOut
	int pIDS[PROCESS_COUNT]; //i processi principali ossia player, audio, clock e coreProcess
	srand((unsigned int) time(NULL));

	initScreen();
	pipe(p);



	if(S_WIDTH < 21 || S_HEIGHT < 22){
		endwin();
		printf("Il terminale non è abbastanza largo per visualizzare correttamente il gioco, assicurati che sia almeno 21 x 21");

		return 0;
	}


	mvprintw(S_HEIGHT/2 - 5, (S_WIDTH-6)/2, "PACMAN"); //\nNCURSES EDITION");
	mvprintw(S_HEIGHT/2 - 4, (S_WIDTH-17)/2, "%cNCURSES EDITION%c", PAC_LEFT, PAC_RIGHT);

	mvprintw(S_HEIGHT/2, (S_WIDTH-33)/2, "INSERISCI UNA MONETA PER INIZIARE");

	

	for(int i = 0; i< 4; i++){
		attron(COLOR_PAIR(BLUE+i));		
		mvprintw(S_HEIGHT/2 +1,  (S_WIDTH-5)/2 + i, "%c", GHOST);		
		attroff(COLOR_PAIR(BLUE+i));
	}
	attron(COLOR_PAIR(YELLOW));		
	mvprintw(S_HEIGHT/2 +1,  (S_WIDTH-3)/2 + 4, "%c", PAC_RIGHT);		
	attroff(COLOR_PAIR(YELLOW));

	mvprintw(S_HEIGHT-2, (S_WIDTH-28)/2, "SCRITTO DA LORENZO L. CONCAS");


	refresh();
	getch();
	cbreak();
	//creazione dei processi vari

	pIDS[0] = fork();
	if(!pIDS[0])
		clockProcess(p[1]);		
	else{
		pIDS[1] = fork();
		if(!pIDS[1])
			audioProcess(p[0], p[1]);
		else{
			pIDS[2] = fork();
			if(!pIDS[2])
				PlayerInput(p[1]);
			else{
				int gameResult = CoreProcess(p[0], p[1]);		
				for(int i = 0; i<PROCESS_COUNT; i++){
					kill(pIDS[i], SIGKILL);
				}
				clearZone(S_WIDTH, S_HEIGHT);
				switch(gameResult){
					case WIN:{						
						mvprintw(S_HEIGHT/2, (S_WIDTH-9)/2, "HAI VINTO");
						mvprintw(S_HEIGHT/2 +1, (S_WIDTH -1)/2, "%c", PAC_LEFT);
						break;
					}
					case LOST:{
						mvprintw(S_HEIGHT/2, (S_WIDTH-9)/2, "HAI PERSO");
						mvprintw(S_HEIGHT/2 +1, (S_WIDTH-1)/2, "%c", GHOST);
						break;
					}
					case GIVEUP:{
						mvprintw(S_HEIGHT/2, (S_WIDTH-14)/2, "TI SEI ARRESO");
						break;
					}
				}
				mvprintw(S_HEIGHT/2 + 5, (S_WIDTH-23)/2, "PREMI ESCAPE PER USCIRE");
				refresh();
				char c;
				do{
					c = getch();
					cbreak();
				}while(c != ESCAPE);
			}
		}
	}



	endwin();
	return 0;
}

