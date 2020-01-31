package:
	stty sane
	rm -f ./PacMan
	gcc -o PacMan  main.c functions.c processes.c -lncurses -lm
	clear
	mkdir PacManGame
	mv PacMan ./PacManGame
	cp *.wav ./PacManGame
	cp PacMan.ttf ./PacManGame
	echo "Before you start the game install the font in the game folder and set it as the terminal font, because every terminal is different it can't be done automatically"
project:
	stty sane
	rm -f ./PacMan
	gcc -o PacMan  main.c functions.c processes.c -lncurses -lm
	clear
	./PacMan	
	
build:
	stty sane
	clear
	gcc -o PacMan main.c functions.c processes.c -lncurses -lm

build_show_all_errors:
	stty sane
	clear
	gcc -o PacMan  main.c functions.c processes.c -lncurses -lm -Wall -Wextra

clean: PacMan
	rm PacMan

fix:
	stty sane
	clear

run:
	./PacMan

