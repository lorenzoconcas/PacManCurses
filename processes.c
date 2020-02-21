 #include "libs.h"

char *dirNames[6] = {"STADY", "LEFT", "RIGHT","UP","DOWN", "DEAD"};
char *processNames[14] = {"PLAYER_PROCESS", "GHOST_PROCESS", "MAIN_PROCESS", "CLOCK_PROCESS", "AUDIO_PROCESS", "BULLET_PROCESS"};
void PlayerInput(int pipe){
	message msg;
	msg.value = 0;
	msg.shoot = false;
	msg.sender = PLAYER_PROCESS;
	while(true){
		char c = getch();
		cbreak();		
		
		switch(c) {
			//movimento a sinistra
			case KEY_LEFT&A_CHARTEXT:
			case 'a':
			case 'A': {
				msg.value  = LEFT;
				break;
			}
			//movimento a destra
			case KEY_RIGHT&A_CHARTEXT:
			case 'd':
			case 'D': {				
				msg.value  = RIGHT;
				break;
			}
			//movimento su
			case KEY_UP&A_CHARTEXT:
			case 'w':
			case 'W': {
				msg.value  = UP;
				break;
			}
			//movimento giu'
			case KEY_DOWN&A_CHARTEXT:
			case 's':
			case 'S': {
				msg.value  = DOWN;
				break;
			}
			case ' ':{
				msg.shoot = true;
				msg.value = 0;
				break;
			}
			case ESCAPE:{ //ESC
				msg.value  = -1;
				break;
			}
		};
		
		write(pipe, &msg, sizeof(message));	
		msg.shoot = false;
		usleep(200);
	}
}

void ghostProcess(int pipeOut, point initial_position, int ghost_id, int direction_hint){
	/*
	* questo processo si occupa di scrivere sul buffer la direzione del fantasmino
	* un modo intelligente per capire se il fantasma ha colliso con un altro è uccidere il processo 
	* quando si scontra e ricrearlo con un hint su quale direzione seguire
	* in questo modo verranno distrutti *due* fantasmi alla volta che veranno subito ricreati
	* questa tecnica evita che il processo debba continuamente leggere e riscriver sul buffer anche dati non suoi
	* 
	* valori richiesti per questa funzione : 
	* pipeOut
	* posizione iniziale, ID del fantasma, direzione suggerita
	*/
	

	message msg;
	

	point current_position =  initial_position;//GetGhostSpawnPoint(ghost_id);
	
	msg.sender = GHOST_PROCESS;
	msg.id = ghost_id;
	
	int direction = direction_hint; //da sostituire con direction_hint
	int cycleCount = 0;
	
	while(true){
		//usleep(GHOST_DELAY/((ghost_id+1)*0.7));
		usleep(GHOST_DELAY/(rnd(ghost_id+1, 5) * 0.4)) ;
		/*
		* Determiniamo la posizione del fantasma
		* in certi punti particolari, come nello spawn o nei portali c'è bisogno di
		* alcuni accorgimenti
		* Dopo aver calcolato la direzione (se necessario) la applichiamo e la trasmettiamo al processo principale	
		*/
		 

		if(isInSpawn(current_position)){
			current_position = GetNextGhostSpawnPosition(current_position);			
		}else{		
						
			/*
			* Controlliamo che il fantasma non sia arrivato ad un portale,
			* in caso lo trasportiamo e forziamo la direzione
			* Se non siamo nei portali procediamo col calcolo della direzione
			*/
			if(current_position.y == 7 && current_position.x == 9 ){ //se è sopra il punto di spawn, prendiamo una direzione
				direction = rnd(LEFT, RIGHT);		
			}
			else if(current_position.y == 9 && current_position.x < 0){ //se è fuori dal alto dx
				current_position.x = 18;
				direction = LEFT;
			}else if(current_position.y == 9 && current_position.x > 18){ //se è fuori dal lato dx
				current_position.x = 0;
				direction = RIGHT;
			}			
			else{

				int possibileDirections[4] =  {0,0,0,0};
				getFreeDirections(current_position, possibileDirections);
				int availableDirections = CountNotZero(possibileDirections, 4);			
			
				switch(availableDirections){
					case 0:{
						//impossibile;						
					}
					case 1:{
						direction = possibileDirections[0];
						break;
					}
					case 2:{
						/*
						* Se si tratta di un moto rettilineo procediamo con la direzione precedente
						* altrimenti decidiamo una nuova direzione, evitando di utilizzare quella precedente e quindi tornare indietro
						*/

						bool horizontal = (possibileDirections[0] == LEFT || possibileDirections[0] == RIGHT) && (possibileDirections[1] == LEFT || possibileDirections[1] == RIGHT);
						bool vertical = (possibileDirections[0] == UP || possibileDirections[0] == DOWN) && (possibileDirections[1] == UP || possibileDirections[1] == DOWN);

						
						if(!(horizontal || vertical)){
							//scegliamo l'altra direzione disponibile
							direction = possibileDirections[0] == getOppositeDirection(direction) ? possibileDirections[1] : possibileDirections[0];												
						}
						break;
					}
					case 3: 	
					case 4:{
						int new_direction = DOWN;

						do{
							new_direction = possibileDirections[rnd(0, availableDirections-1)];
						}while(new_direction == getOppositeDirection(direction)); //finchè la direzione non è quella oppposta, non vogliamo che torni indietro senza motivo
						direction = new_direction;
						break;
					}
				}

			}
		}

		//e qui applichiamo la direzione
		switch(direction){
				case LEFT:	{ 	current_position.x--; break;}
				case RIGHT:	{	current_position.x++; break;}
				case UP:	{   current_position.y--; break;}
				case DOWN:	{  	current_position.y++; break;}
		}

		msg.value = direction;
		msg.position = current_position;
		msg.shoot = rnd(0, RANDOM_SHOT_PROBABILITY) == 0 ? true : false; 
		
		//logMessage("ghost_message.txt",  msg);
		write(pipeOut, &msg, sizeof(message));	
		cycleCount++;
	}
}


int CoreProcess(int pipeIn, int pipeOut){

	//variabili e assegnazione dei valori iniziali
	point ghostsPosition[GHOSTS];// = getGhostSpawn();
	bulletS *bulletsPosition = NULL;
	point collectibles[collectible_pointsSize()];
	point special_collectibles[SPECIAL_POINTS];	
	point player_position = {9,15}; //aka player start position
	point cherryPoint =  {-1, -1};
	point futureSpawn = {-1, -1};
	char player_icon = PAC_RIGHT;
	
	//int currentClock = 0;
	int attackingTimer = 0;
	int points = 0;
	int lifes = 3;
	int cherryCount = 0;
	int bulletTaken = 0;
	int bulletsSize = 0;
	int ghostDirections[4];
	int gameResult = 0;
	int spawnCountDown = 0;
	bool exit = false;
	bool attacking = false;	

	message audioMsg;

	audioMsg.sender = MAIN_PROCESS;
	audioMsg.receiver = AUDIO_PROCESS;
	getCollectibles(collectibles);
	getSpecialCollectibles(special_collectibles);
	getGhostSpawn(ghostsPosition);

	ghostsPosition[3].x = -1;
	ghostsPosition[3].y = -1;

	
	//fcntl(pipeOut, F_SETFL, O_NONBLOCK);

	/*Inizio logica di gioco*/
	drawScene(player_position, player_icon, collectibles, special_collectibles, ghostsPosition, bulletsPosition, bulletsSize, attacking, points, lifes, cherryPoint);	
	system(getAudio(BEGIN));

	int gIDS[4];
	int *bIDS = NULL;

	gIDS[0] = fork();
	if(!gIDS[0]){
		usleep(GHOST_DELAY);
		ghostProcess(pipeOut, ghostsPosition[0], 0, STADY);				
		while(true);
	}
	gIDS[1] = fork();
 	if(!gIDS[1]){
		ghostProcess(pipeOut, ghostsPosition[1], 1, STADY);	
		while(true);		
	}
	gIDS[2] = fork();
	if(!gIDS[2]){
		ghostProcess(pipeOut, ghostsPosition[2], 2, STADY);	
		while(true);			
	}		
	/*gIDS[3] = fork(); //questo fantasma viene generato casualmente quando un pallino viene mangiato
	if(!gIDS[3]){
		ghostProcess(pipeOut, ghostsPosition[3], 3, STADY);
		while(true);				
	}	*/ 

	
	
	while(lifes > 0 || exit){
		clearScreen();
		message incoming_msg;
		incoming_msg.sender = -1;
		incoming_msg.value = -1; 
		incoming_msg.shoot = false;

		//leggiamo i dati dalla pipe
		read(pipeIn, &incoming_msg, sizeof(message));
		switch(incoming_msg.sender){
			case PLAYER_PROCESS:{
				if(spawnCountDown > 0)
					spawnCountDown++;

				int direction = incoming_msg.value;
				switch(direction){
					case LEFT:  {	player_position.x--; player_icon = PAC_LEFT;   break;}
					case RIGHT: {	player_position.x++; player_icon = PAC_RIGHT;  break;}
					case UP:	{	player_position.y--; 						   break;}
					case DOWN:  {	player_position.y++; 						   break;}
					case -1:	{	exit = true;						   return GIVEUP;}
				}
				//teletrasporto dei portali
				if(player_position.y == 9){
					//se è fuori da lato sx
					if(player_position.x < 0)
						player_position.x = 18;
					//se è fuori dal lato dx
					if(player_position.x > 18)
						player_position.x = 0;
				}
				//controllo collisioni coi muri
				if(isCollidingWithWall(player_position)){					
					switch(direction){
						case LEFT:	{	player_position.x++; break;}
						case RIGHT: {	player_position.x--; break;}
						case UP:	{	player_position.y++; break;}
						case DOWN: 	{	player_position.y--; break;}
					}
				}
				//tempo di mangiare qualche pallino
				for(int i = 0; i < collectible_pointsSize(); i++){
					if(player_position.y == collectibles[i].y && player_position.x == collectibles[i].x ){
						//qui si deve decidere se far spawnare il quarto fantasma
						
						if(ghostsPosition[3].x < 1 && rnd(0, GHOST_SPAWN_PROBABILITY) == 0){
							futureSpawn = collectibles[i];
							spawnCountDown++;
						}

						collectibles[i].y = -1;
						collectibles[i].x = -1;
						points += POINT_VALUE;
						audioMsg.value = EAT;
						write(pipeOut, &audioMsg, sizeof(message));
					}
				}
				for(int i = 0; i < SPECIAL_POINTS; i++){
					if(isSamePoint(player_position, special_collectibles[i])){ //player_position.y == special_collectibles[i].y && player_position.x == special_collectibles[i].x ){
						special_collectibles[i].y = -1;
						special_collectibles[i].x = -1;
						points += SPECIAL_POINT_VALUE;
						attackingTimer = 0;
						attacking = true;
						audioMsg.value = EAT;
						write(pipeOut, &audioMsg, sizeof(message));					
					}
				}

				if(isSamePoint(player_position, cherryPoint)){
					cherryCount++;
					if(cherryCount >= 3){
						lifes++;
						cherryCount = 0;
					}
				
					cherryPoint.x = -1;
					cherryPoint.y = -1;
					audioMsg.value = FRUIT;
					write(pipeOut, &audioMsg, sizeof(message));
					audioMsg.value = NEW_LIFE;
					write(pipeOut, &audioMsg, sizeof(message));				
				}

				for(int i = 0; i<bulletsSize; i++){
					if(bulletsPosition[i].target == PLAYER_PROCESS && isSamePoint(bulletsPosition[i].position, incoming_msg.position)){
					
						bulletsPosition[i].position.x = -1;
						bulletsPosition[i].position.y = -1;
						kill(bIDS[i], SIGKILL);
						bulletTaken++;
					}
				}


				if(incoming_msg.shoot){			
					bulletsSize += 4;
					if(bulletsPosition == NULL)
						bulletsPosition = (bulletS*)malloc(4*sizeof(bulletS));
					else
						bulletsPosition = (bulletS*)realloc(bulletsPosition, bulletsSize*sizeof(bulletS));

					if(bIDS == NULL)
						bIDS = (int*)malloc(4*sizeof(int));
					else
						bIDS = (int*)realloc(bIDS, bulletsSize * sizeof(int));
						

					for(int i = 0; i < 4; i++){
						bIDS[bulletsSize-1-i] = fork();
						if(!bIDS[bulletsSize-1-i]){
							BulletProcess(pipeOut,player_position, i+1, bulletsSize-1-i, incoming_msg.sender);
							while(true);
						}
					}			
				}

				if(bulletTaken >= 10){
					bulletTaken = 0;
					lifes--;
					resetPlayer;
				}		


				break;
			}
			case CLOCK_PROCESS:{
				if(attacking)
					attackingTimer++;
				
				break;
			}
			case GHOST_PROCESS:{
				int id = incoming_msg.id;				
				ghostsPosition[id] = incoming_msg.position;
				ghostDirections[id] = incoming_msg.value;
				int otherGhost = -1;

				if(!isInCollisionAllowedArea(ghostsPosition[id])){
					otherGhost = isGhostCollidingWithOthers(id, ghostsPosition);
					if(otherGhost != -1){
						//spostiamo preventivamente uno dei due fantasmi per evitare che si incastrino in un loop
						switch(getOppositeDirection(ghostDirections[otherGhost])){ 
							case LEFT:	{ 	ghostsPosition[otherGhost].x--; break;}
							case RIGHT:	{	ghostsPosition[otherGhost].x++; break;}
							case UP:	{   ghostsPosition[otherGhost].y--; break;}
							case DOWN:	{  	ghostsPosition[otherGhost].y++; break;}
						}
					
						//eliminiamo direttamente i processi e li ricreiamo
					
						kill(gIDS[id], SIGKILL);
						kill(gIDS[otherGhost], SIGKILL);
						gIDS[id] = fork();
						if(!gIDS[id]){
							usleep(GHOST_DELAY);
							ghostProcess(pipeOut, ghostsPosition[id], id, getOppositeDirection(ghostDirections[id]));				
							while(true);
						}
						gIDS[otherGhost] = fork();
						if(!gIDS[otherGhost]){
							usleep(GHOST_DELAY);
							ghostProcess(pipeOut, ghostsPosition[otherGhost], otherGhost, getOppositeDirection(ghostDirections[otherGhost]));				
							while(true);
						}
					}				
				}

				//controlliamo che i fantasmi non abbiano colliso coi proiettili
				
				for(int i = 0; i<bulletsSize; i++){
					if(bulletsPosition[i].target == GHOST_PROCESS && isSamePoint(bulletsPosition[i].position, incoming_msg.position)){
					
						bulletsPosition[i].position.x = -1;
						bulletsPosition[i].position.y = -1;
						kill(bIDS[i], SIGKILL);
						kill(gIDS[id], SIGKILL);
						gIDS[id] = fork();
						if(!gIDS[id]){
							usleep(GHOST_DELAY);
							ghostsPosition[id] = getGhostSpawn2(id);
							ghostProcess(pipeOut, ghostsPosition[id], id, STADY);				
							while(true);
						}

					}
				}

				//se il fantasma ha deciso di sparare
				if(incoming_msg.shoot){
					bulletsSize += 4;

					if(bulletsPosition == NULL)
						bulletsPosition = (bulletS*)malloc(4*sizeof(bulletS));
					else
						bulletsPosition = (bulletS*)realloc(bulletsPosition, bulletsSize*sizeof(bulletS));

					if(bIDS == NULL)
						bIDS = (int*)malloc(4*sizeof(int));
					else
						bIDS = (int*)realloc(bIDS, bulletsSize * sizeof(int));
					

					for(int i = 0; i < 4; i++){
						bIDS[bulletsSize-1-i] = fork();
						if(!bIDS[bulletsSize-1-i]){
							BulletProcess(pipeOut, player_position, i+1, bulletsSize-1-i, incoming_msg.sender);							
							while(true);

						}
					}					
				}


				//controlliamo che non abbia colliso col player
				
				if(isSamePoint(incoming_msg.position, player_position)){
					//collisione
					if(attacking){ //il player mangia il fantasma
						points += 10;
						ghostsPosition[id] = GetGhostSpawnPoint(id);
						audioMsg.value = GHOST_EAT;
						write(pipeOut, &audioMsg, sizeof(message));			
						kill(gIDS[id], SIGKILL);
						gIDS[id] = fork();
						if(!gIDS[id]){
							usleep(GHOST_DELAY*10);
							ghostProcess(pipeOut, ghostsPosition[id], id, STADY);				
							while(true);
						}


					}else{
						lifes--;
						resetPlayer;
							system(getAudio(DEATH));
						
					
						for(int i = 0; i<GHOSTS; i++){
							kill(gIDS[i], SIGKILL);		
						
							ghostsPosition[i] = GetGhostSpawnPoint(i);
							gIDS[i] = fork();
							if(!gIDS[i]){
								usleep(GHOST_DELAY);
								ghostProcess(pipeOut, ghostsPosition[i], i, STADY);				
								while(true);
							}
						}						
					}
				}
				break;
			}
			case BULLET_PROCESS:{
				int id = incoming_msg.id;				
				bulletsPosition[id].position = incoming_msg.position;
				bulletsPosition[id].target = incoming_msg.receiver;				
				break;
			}
		}

		if(attackingTimer >= 6){
			attackingTimer = 0;
			attacking = false;
		}
		if(lifes < 1)
			gameResult = LOST;
		else{
			int eaten = eatenPoints(collectibles, collectible_pointsSize()) + eatenPoints(special_collectibles, 4);
			if(eaten == SPECIAL_POINTS + NORMAL_POINTS)
				return WIN;

		}

		//questo codice fa spawnare il fantasma a distanza di tre movimenti dal giocatore
		if(spawnCountDown > 3){
			spawnCountDown = 0;
			ghostsPosition[3] = futureSpawn;
			gIDS[3] = fork(); //questo fantasma viene generato casualmente quando un pallino viene mangiato
			if(!gIDS[3]){
				ghostProcess(pipeOut, ghostsPosition[3], 3, STADY);
				while(true);				
			}
		}
		if(cherryPoint.x < 0)
			cherryPoint = rnd(0, CHERRY_PROBABILITY) == 0 ? getCherryPoint() : cherryPoint;
		drawScene(player_position, player_icon, collectibles, special_collectibles, ghostsPosition, bulletsPosition, bulletsSize, attacking, points, lifes, cherryPoint);			
		
	}
	return gameResult;
}

void BulletProcess(int pipeOut, point initial_position, int direction, int id, int sender){


	message msg;
	msg.sender = BULLET_PROCESS;
	msg.receiver = sender == PLAYER_PROCESS ? GHOST_PROCESS : PLAYER_PROCESS;
	msg.id = id;
	msg.shoot = 0;
	point bullet_position = initial_position;
	int bullet_direction = direction;

	
	while(true){
		switch(bullet_direction){
			case LEFT:	{ 	bullet_position.x--; break;}
			case RIGHT:	{	bullet_position.x++; break;}
			case UP:	{   bullet_position.y--; break;}
			case DOWN:	{  	bullet_position.y++; break;}
		}		
		if(bullet_position.y == 9){
			if(bullet_position.x == 0)
				bullet_position.x = 19;
			else if(bullet_position.x == 19)
				bullet_position.x = 0;
		}
		if(isCollidingWithWall(bullet_position)){
			bullet_direction = DEAD;	
			bullet_position.x = -1;
			bullet_position.y = -1;			
		}

		msg.value = bullet_direction;
		msg.position = bullet_position;
		write(pipeOut, &msg, sizeof(message));	
		if(msg.value == DEAD)
			suicide;
		usleep(GHOST_DELAY);
	}

}
