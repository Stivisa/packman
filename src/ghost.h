#include "game.h"
#include "scene.h"
#define FAST_GHOST 5
#define SLOW_GHOST 5

int start_x_blue;	//pocetna pozicija
int start_z_blue;
int ghost_blue_x;	//trenutna pozicija
int ghost_blue_z;
int move_blue_ghost;	// 1 za desno , 2 dole , 3 levo , 4 gore
int last_blue_ghost_move;	//prethodni potez , jer mu ne dam da se vraca unazad(zanimljivije)
int direction_blue_ghost;	//treba ga i rotirati
int broj_poteza;	//broj mogucih poteza
int broj_blue;
int opcije_blue[4];	// moguci potezi
int exit_blue;		// prva kretanja sam ja zadao (da ne idu zajedno ...)
//int izabran_blue;	// random broj , na osnovu njega uzimamo vrednost iz mogucih poteza
int move_options(int ghost_x,int ghost_z,int last_move,int* opcije);	//popunjava opcije_blue[]
int blue_eaten;		//da li je pojeden od pacmana

void must_go_back(int* last , int* next);

void choose_move( int num , int* last, int* next , int* opcije);

void set_direction(int next , int* direction);

int start_x_pink;
int start_z_pink;
int ghost_pink_x;
int ghost_pink_z;
int move_pink_ghost;
int last_pink_ghost_move;
int direction_pink_ghost;
int broj_pink;
int opcije_pink[4];
int exit_pink;
//int izabran_pink;
//int move_options_pink(int ghost_x,int ghost_z,int last_move , int* opcije);
int pink_eaten;

int start_x_purple;
int start_z_purple;
int ghost_purple_x;
int ghost_purple_z;
int move_purple_ghost;
int last_purple_ghost_move;
int direction_purple_ghost;
int broj_purple;
int opcije_purple[4];
int exit_purple;
//int izabran_purple;
//int move_options_purple(int ghost_x,int ghost_z,int last_move,int* opcije);
int purple_eaten;

int start_x_lightblue;
int start_z_lightblue;
int ghost_lightblue_x;
int ghost_lightblue_z;
int move_lightblue_ghost;
int last_lightblue_ghost_move;
int direction_lightblue_ghost;
int broj_lightblue;
int opcije_lightblue[4];
int exit_lightblue;
//int izabran_lightblue;
//int move_options_lightblue(int ghost_x,int ghost_z,int last_move,int* opcije);
int lightblue_eaten;

int l;

int animation_ghost;		// za timer kretanja
float animation_ghost_parameter;
int animation_movement_parameter; // za timer koji poziva timer kretanja 

int GHOST_TIMER_SPEED;

void pacman_eat_ghost();
void ghost_eat_packman();
void ghost_movement();
void ghost_timer(int value);	//animacija kretanja
void move_all_ghosts_timer(int value); // timer koji poziva timer za animaciju kretanja
int next_ghost_move(int ghost_x,int ghost_z,int right,int down, int left, int up); // da li je moguc potez
