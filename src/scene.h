#ifndef _SCENE_H_
#define _SCENE_H_

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "txloader.h"
#include "ghost.h"

//#define map sizes 

int map[15][30];
int intro;	//ponistava pocetnu sliku

void make_scene(void);
void make_wall(void);
void make_character(void);
void make_points(void);
void make_extra_points(void);
void make_ghosts(int p);
void scoreboard();	// rezultat iscrtava
void make_ghost_eyes();
void bonus_ghost_color();

#endif
