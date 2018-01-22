#include <GL/glut.h>
#include <GL/gl.h>
#include "scene.h"
#include <string.h>
#include <time.h>

#define NORMAL_TIMER 5 //milisekunde za timer kod pacmana
#define FAST_TIMER 0

int start_x;	// pocetna pozicija igraca, tu ga vracamo kad je pojeden
int start_z;

int x_coordinate;	// trenutna pozicija igraca
int z_coordinate;
int move;	        // 1 za desno , 2 dole , 3 levo , 4 gore
int direction;
int animation_active;		//promenljive za timer
float animation_parameter;
int pause;
int score;
int life;
int TIMER_SPEED;
//GLuint tex1;
//GLuint tex2;

time_t seconds1;	//vreme za bonus time
time_t seconds2;
int bonus_time;

void set_begining();
int next_move(int right,int down, int left, int up); //provera potez sledeci
void on_keyboard(unsigned char key, int x, int y);
void on_reshape(int width, int height);
void on_display(void);
void on_timer(int value);
//void restart();	u pocetku krenu da prolaze kroz zidove duhovi...
void eat_point();
int is_eaten(int i,int j);
