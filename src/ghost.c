#include "ghost.h"
#include <stdio.h>
#include <stdlib.h>
//#include <time.h>

void ghost_movement(){
	if(!bonus_time)
		ghost_eat_packman();
	if(bonus_time)
		pacman_eat_ghost();
	
	//broj opcija za kretanje
	broj_blue = move_options(ghost_blue_x,ghost_blue_z,last_blue_ghost_move , opcije_blue );
		
	broj_pink = move_options(ghost_pink_x,ghost_pink_z,last_pink_ghost_move , opcije_pink);
		
	broj_purple = move_options(ghost_purple_x,ghost_purple_z,last_purple_ghost_move , opcije_purple);
		
	broj_lightblue = move_options(ghost_lightblue_x,ghost_lightblue_z,last_lightblue_ghost_move, opcije_lightblue);	
	
	//bira se neka od mogucih kretnji
	choose_move(broj_blue ,&last_blue_ghost_move, &move_blue_ghost , opcije_blue);
	
	choose_move(broj_pink ,&last_pink_ghost_move, &move_pink_ghost , opcije_pink);
	
	choose_move(broj_purple ,&last_purple_ghost_move, &move_purple_ghost,opcije_purple);
	
	choose_move(broj_lightblue ,&last_lightblue_ghost_move, &move_lightblue_ghost,opcije_lightblue);
	
	
	//**pocetni potezi botova , da ne bude mnogo dosadno
	if(exit_blue<5){	
		move_blue_ghost=1;
		if(exit_blue==4)
			move_blue_ghost=4;
		exit_blue++;
	}
	if(exit_pink<6){
		move_pink_ghost=1;
		if(exit_pink==5)
			move_pink_ghost=4;
		exit_pink++;
	}
	if(exit_lightblue<7){
		move_lightblue_ghost=1;
		if(exit_lightblue>=4)
			move_lightblue_ghost=2;
		if(exit_lightblue==6)
			move_lightblue_ghost=3;
		exit_lightblue++;
	}
	if(exit_purple<8){
		move_purple_ghost=1;
		if(exit_purple>=5)
			move_purple_ghost=2;
		exit_purple++;
	}
	
	// postavljamo direction tj. u koju stranu rotiramo ghosta
	set_direction(move_blue_ghost , &direction_blue_ghost);
	set_direction(move_pink_ghost , &direction_pink_ghost);
	set_direction(move_purple_ghost , &direction_purple_ghost);
	set_direction(move_lightblue_ghost , &direction_lightblue_ghost);
		
	if(!animation_ghost){
		animation_ghost=1;	
		glutTimerFunc(GHOST_TIMER_SPEED, ghost_timer, 0);
	}		
}
int move_options(int ghost_x,int ghost_z,int last_move ,int* opcije){// 1 za desno , 2 dole , 3 levo , 4 gore
	//last_move!=3, ako je isao bot desno , onda mu ne dam da ide levo tj. da se vrati,zanimljivije	
	broj_poteza = 0;
	if(next_ghost_move(ghost_x,ghost_z,1,0,0,0) && last_move!=3){
		opcije[broj_poteza++]=1;		
	}
	if(next_ghost_move(ghost_x,ghost_z,0,1,0,0) && last_move!=4){
		opcije[broj_poteza++]=2;		
	}
	if(next_ghost_move(ghost_x,ghost_z,0,0,1,0) && last_move!=1){
		opcije[broj_poteza++]=3;		
	}
	if(next_ghost_move(ghost_x,ghost_z,0,0,0,1) && last_move!=2){
		opcije[broj_poteza++]=4;	
	}
	return broj_poteza;
}

void choose_move(int num ,int* last, int* next , int* opcije){
      int chs =0;
      if(num != 0){ //ako nije 0 uzimamo neku random kretnju koja je moguca
	chs = rand() % num; 
	*next=opcije[chs]; 
      }
      else //kada mora unazad da se vrati,zbog mape...(posto mu ne dam da se vraca unazad ,zanimljivije)
	must_go_back(last , next);
	
      *last = *next;
    
}
void must_go_back(int* last , int* next){
	if(*last==1)		*next=3;
	else if(*last==3)	*next=1;
	else if(*last==4)	*next=2;
	else if(*last==2)	*next=4; 
}
void set_direction(int next , int* direction){
	// 1 za desno , 2 dole , 3 levo , 4 gore
	if(next == 1)		*direction=90;
	else if(next == 2)	*direction=0;
	else if(next == 3)	*direction=-90;
	else if(next == 4)	*direction=180;
  
}
void ghost_timer(int value){
	if (value != 0)
        return;
	if(!pause)
	animation_ghost_parameter+=2;
	//pomeramo za jedno polje	
	if(animation_ghost_parameter>10 && !pause){
		animation_ghost=0;
		animation_ghost_parameter=0;
		switch(move_blue_ghost){
			case 1 : ghost_blue_x+=1;
		
				 break;
			case 2 : ghost_blue_z+=1; 
				 	 	
				 break;
			case 3 : ghost_blue_x-=1;
				 
				 break;
			case 4 : ghost_blue_z-=1;
				
				break;
		}
		switch(move_pink_ghost){
			case 1 : ghost_pink_x+=1;
		
				 break;
			case 2 : ghost_pink_z+=1; 
				 	 	
				 break;
			case 3 : ghost_pink_x-=1;
				 
				 break;
			case 4 : ghost_pink_z-=1;
				
				break;
		}
		switch(move_purple_ghost){
			case 1 : ghost_purple_x+=1;
		
				 break;
			case 2 : ghost_purple_z+=1; 
				 	 	
				 break;
			case 3 : ghost_purple_x-=1;
				 
				 break;
			case 4 : ghost_purple_z-=1;
				
				break;
		}
		switch(move_lightblue_ghost){
			case 1 : ghost_lightblue_x+=1;
		
				 break;
			case 2 : ghost_lightblue_z+=1; 
				 	 	
				 break;
			case 3 : ghost_lightblue_x-=1;
				 
				 break;
			case 4 : ghost_lightblue_z-=1;
				
				break;
		}
	}
	glutPostRedisplay();
	
	if (animation_ghost){
		glutTimerFunc(GHOST_TIMER_SPEED, ghost_timer, 0);
	}
}
int next_ghost_move(int ghost_x,int ghost_z,int right,int down, int left, int up){
	int x=ghost_x+right-left;
	int z=(ghost_z-up+down)*(-1);
	
	// ukoliko je naredno prazno polje tj. polje sa poenima moze da se pomeri
	if((map[x][z]==0 || map[x][z]==3 || map[x][z]==2 || map[x][z]==8 || map[x][z]==4 || map[x][z]==5|| map[x][z]==6 || map[x][z]==7) && !pause) 
		return 1;
	
	return 0;
}
void move_all_ghosts_timer(int value){ //packman krece na tastaturu , a ovo pokrece botove
	if (value != 0)
        return;
	if(!pause){
		animation_movement_parameter+=2;	
		if(animation_movement_parameter>10){
			animation_movement_parameter=0;
			ghost_movement();
		}
	
		if (animation_movement_parameter<=10){
			glutTimerFunc(GHOST_TIMER_SPEED, move_all_ghosts_timer, 0);
		}
	}
}
void ghost_eat_packman(){
	int x,z;
	int pojeden=0;
	x=x_coordinate;
	z=z_coordinate*(-1);
	// ako su im koordinate iste , onda igrac gubi zivot
	if((x==ghost_blue_x)&&(z==ghost_blue_z*(-1))){
		pause=1;
		life--;
		pojeden=1;
	}
	if((x==ghost_pink_x)&&(z==ghost_pink_z*(-1))){
		pause=1;
		life--;
		pojeden=1;
	}
	if((x==ghost_lightblue_x)&&(z==ghost_lightblue_z*(-1))){
		pause=1;
		life--;
		pojeden=1;	
	}
	if((x==ghost_purple_x)&&(z==ghost_purple_z*(-1))){
		pause=1;
		life--;
		pojeden=1;
	}
	if(pojeden){ // vracam ih na pocetne pozicije , pojedeni poeni zapamceni
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

		direction=0;
		direction_pink_ghost=0;
		direction_blue_ghost=0;
		direction_lightblue_ghost=0;
		direction_purple_ghost=0;

		exit_blue=0;
		exit_pink=0;
		exit_lightblue=0;
		exit_purple=0;
		
		//pojeden=0;
	}
	
}
void pacman_eat_ghost(){
	int x,z;
	//int pojeden=0;
	x=x_coordinate;
	z=z_coordinate*(-1);
	//iste koordinate , vraca bota na pocetnu poziciju
	if((x==ghost_blue_x)&&(z==ghost_blue_z*(-1))){
		ghost_blue_x=start_x_blue;
		ghost_blue_z=start_z_blue;
		exit_blue=0;
		direction_blue_ghost=0;
		//blue_eaten=1;
	}
	if((x==ghost_pink_x)&&(z==ghost_pink_z*(-1))){
		ghost_pink_x=start_x_pink;
		ghost_pink_z=start_z_pink;
		exit_pink=0;
		direction_pink_ghost=0;
		//pink_eaten=1;
	}
	if((x==ghost_lightblue_x)&&(z==ghost_lightblue_z*(-1))){
		ghost_lightblue_x=start_x_lightblue;
		ghost_lightblue_z=start_z_lightblue;
		exit_lightblue=0;
		direction_lightblue_ghost=0;
		//lightblue_eaten=1;	
	}
	if((x==ghost_purple_x)&&(z==ghost_purple_z*(-1))){
		ghost_purple_x=start_x_purple;
		ghost_purple_z=start_z_purple;
		exit_purple=0;
		direction_purple_ghost=0;
		//purple_eaten=1;
	}
}
