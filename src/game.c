#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "game.h"

void set_begining(){
	glutKeyboardFunc(on_keyboard);
	glutReshapeFunc(on_reshape);
	glutDisplayFunc(on_display);
	TIMER_SPEED = NORMAL_TIMER;
	GHOST_TIMER_SPEED = FAST_GHOST;
	score=0;
	life=3;	
	
	time_t t;		// biramo random brojeve , za smer kretanja ghost (botova)
	srand(time(&t));
	
	FILE *fajl;		
	//ucitava mapa koja je data .txt fajlom
	if ((fajl = fopen("map.txt", "r")) == NULL){
		printf("Can't open file");
		exit(1);         
	}
	int i,j;
	for(i=0;i<15;i++){
		for(j=0;j<26;j++){
			fscanf(fajl, "%d", &map[i][j]);
			if(map[i][j]==2){ 	//pacman
				start_x = i;				
				start_z = -j;

				x_coordinate=i; //pamtimo pocetnu poziciju zbog kretanja
				z_coordinate=-j;
			}
			if(map[i][j]==4){	//blue ghost
				start_x_blue = i;				
				start_z_blue = -j;
				ghost_blue_x=i; 
				ghost_blue_z=-j;
			}
			if(map[i][j]==7){	//pink
				start_x_pink = i;				
				start_z_pink = -j;
				ghost_pink_x=i; 
				ghost_pink_z=-j;
			}
			if(map[i][j]==6){	//purple
				start_x_purple = i;				
				start_z_purple = -j;
				ghost_purple_x=i; 
				ghost_purple_z=-j;
			}
			if(map[i][j]==5){	//lightblue
				start_x_lightblue = i;				
				start_z_lightblue = -j;
				ghost_lightblue_x=i; 
				ghost_lightblue_z=-j;
			}
		}		
	}
}
void on_keyboard(unsigned char key, int x, int y){
	switch (key) {
	case 27:
		/* Zavrsava se program. */
		exit(0);
		break;
	case 'd':
   	case 'D'://kretanje desno
		
		if(!animation_active && next_move(1,0,0,0)){ //ako miruje i ako je moguc potez udesno
			animation_active=1;
			move=1;		// 1 za desno , 2 dole , 3 levo , 4 gore
			direction=90;	//treba da i rotiramo udesno
			glutTimerFunc(TIMER_SPEED, on_timer, 0); //poziva animacija pokreta	
		}	
       		break;
	case 's':
   	case 'S':
        	if(!animation_active && next_move(0,1,0,0)){
			animation_active=1;
			move=2;
			direction=0;
			glutTimerFunc(TIMER_SPEED, on_timer, 0);		
		}
       		break;
	case 'a':
   	case 'A':
        	if(!animation_active && next_move(0,0,1,0)){
			animation_active=1;
			move=3;
			direction=-90;
			glutTimerFunc(TIMER_SPEED, on_timer, 0);
		}
       		break;
	case 'w':
   	case 'W':
        	if(!animation_active && next_move(0,0,0,1)){
			
			animation_active=1;
			move=4;
			direction=180;
			glutTimerFunc(TIMER_SPEED, on_timer, 0);
		}
       		break;
	/*case 'r':   //timeri timeri i onda problemi prilikom prvih poteza nakon restarta
			// tj naprave koji pokret kroz zid , mada nakon tih pocetnih poteza nema problema
   	case 'R':
		pause = 1;
		direction_pink_ghost=0;
		direction_blue_ghost=0;
		direction_lightblue_ghost=0;
		direction_purple_ghost=0;

		//pause =0;
		exit_blue=0;
		exit_pink=0;
		exit_lightblue=0;
		exit_purple=0;
        	set_begining();
		glutPostRedisplay();
       		break;*/
	case 'p':
   	case 'P':
		if(!pause) pause=1;	
		else {pause = 0;
		glutTimerFunc(0, move_all_ghosts_timer, 0);	//fja koja non stop poziva kretanja ghost
		}
		break;
	case 'y':
   	case 'Y':		//pokrece igricu ...
		pause=0;
		intro =1; 
		glutPostRedisplay(); //mozda i ne mora
		glutTimerFunc(0, move_all_ghosts_timer, 0);
       		break;
	}
}
/*void restart(){
	pause = 1;
	ghost_blue_x=start_x_blue;
	ghost_blue_z=start_z_blue;
	ghost_pink_x=start_x_pink;
	ghost_pink_z=start_z_pink;
	ghost_lightblue_x=start_x_lightblue;
	ghost_lightblue_z=start_z_lightblue;
	ghost_purple_x=start_x_purple;
	ghost_purple_z=start_z_purple;
	x_coordinate = start_x;
	z_coordinate = start_z;

	direction_pink_ghost=0;
	direction_blue_ghost=0;
	direction_lightblue_ghost=0;
	direction_purple_ghost=0;

	exit_blue=0;
	exit_pink=0;
	exit_lightblue=0;
	exit_purple=0;
    
}*/
int next_move(int right,int down, int left, int up){
	int x=x_coordinate+right-left;
	int z=(z_coordinate-up+down)*(-1);
	
	// ukoliko je polje prazno ili sa poenima , moze da se pomeri
	if((map[x][z]==0 || map[x][z]==3 || map[x][z]==2 || map[x][z]==8) && !pause) return 1;
	
	return 0;
}
void on_timer(int value){
	if (value != 0)
        return;

	animation_parameter+=3;
	//pomeramo za jedno polje	
	if(animation_parameter>10){
		animation_active=0;
		animation_parameter=0;
		switch(move){
			case 1 : x_coordinate+=1;
				eat_point(x_coordinate,z_coordinate); //kad promenimo polozaj uzimamo poene
	
				 /*if(!(next_move(1,0,0,0))) 
				daje smooth kretanje ali ne menja pravac do zida
					animation_active=0;*/		
				 break;
			case 2 : z_coordinate+=1; 
				 eat_point(x_coordinate,z_coordinate);
					 	
				 break;
			case 3 : x_coordinate-=1;
				 eat_point(x_coordinate,z_coordinate);
				 break;
			case 4 : z_coordinate-=1;
				eat_point(x_coordinate,z_coordinate);
				break;
		}
	}
	if(!bonus_time)
		ghost_eat_packman();
	if(bonus_time)	//bonus time packman moze jesti botove
		pacman_eat_ghost();

	glutPostRedisplay();
	
	if (animation_active){
		glutTimerFunc(TIMER_SPEED, on_timer, 0);
	}
}
int is_eaten(int i,int j){ 
	seconds2 = time(NULL);
	if(bonus_time){
		seconds2 = time(NULL);
		if(seconds2-seconds1 == 4){  //bonus time traje 4 sekunde

			blue_eaten=0;
			pink_eaten=0;
			lightblue_eaten=0;
			purple_eaten=0;
	
			TIMER_SPEED=NORMAL_TIMER;	//usorava packmana
			GHOST_TIMER_SPEED=FAST_GHOST;	//vraca brzinu botovima
			bonus_time=0;
		}
	}
	if(map[i][j] == 2) // govori da na polju nema vise poena
		return 1;
	if(map[i][j] == 8)
		return 1;
	else
		return 0;
}
void eat_point(int x,int z){
	x=x_coordinate;
	z=z_coordinate*(-1);
	
	if(!(is_eaten(x,z))){
		if(map[x][z]==0)		//obicni poeni
			score+=100;
		else if(map[x][z]==3){		//extra poeni
			score+=300;

	   		seconds1 = time(NULL);
			bonus_time=1;
			TIMER_SPEED=FAST_TIMER;
			GHOST_TIMER_SPEED=SLOW_GHOST;
			
		}
		map[x][z]=8; //pojedi
		glPushMatrix();
		GLfloat black[] = {0,0,0,1};
		glMaterialfv(GL_FRONT, GL_AMBIENT, black);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, black);
		scoreboard();			// updajtuje rezultat
		glPopMatrix();
	}

}
void on_reshape(int width, int height)
{
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30, (float) width / height, 1, 1000);
}

void on_display(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();	
	
	gluLookAt(50,350, 200, 50, 0, -100, 0, 1, 0);
	
	make_scene(); //fja iz scene.c koja iscrtava scenu

	glutSwapBuffers();
}
