#include "scene.h"
#include "game.h"

void make_scene(void){

	// ucitavam bmp slike preko txloader.c ,POZAJMIO SA INTERNETA , NISAM MOGAO BEZ TOGA :)
	if(score>=8000){	//pobeda
		GLuint tex1 = loadTex("yw.bmp");	
		banner(tex1);
		pause =1;
	}
	if(life==0){		//poraz
		GLuint tex2 = loadTex("go.bmp");
		banner(tex2);
		pause =1;
	}
	if(!intro){		//pocetna slika
		GLuint tex3 = loadTex("intro24.bmp");
		banner(tex3);
		pause =1;
		glutPostRedisplay();
	}		
	
	glPushMatrix();
	GLfloat ambient_coeffs_green[] 	= {0,0,0,1};
	GLfloat diffuse_coeffs_green[] 	= {0,0,0,1};
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs_green);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs_green);
	scoreboard();
	glPopMatrix();

	int i,j;
	//citam map[][] i crtam zidove , karaktera , botove ,poene ... pocetna postavka
	for(i=0;i<10;i++){
		for(j=0;j<26;j++){
			if(map[i][j]==1){
				glPushMatrix();
				glTranslatef(i*10, 0, j*(-10));
				make_wall();
				glPopMatrix();
			}
			if(map[i][j]==2){
				glPushMatrix();
				make_character();
				glPopMatrix();
			}
			if(map[i][j]==4 || map[i][j]==7 || map[i][j]==6 || map[i][j]==5){
				glPushMatrix();
				make_ghosts(map[i][j]);
				glPopMatrix();
			}
			if(map[i][j]==0){
				glPushMatrix();
				glTranslatef(i*10, 0, j*(-10));
				make_points();
				glPopMatrix();
			}
			if(map[i][j]==3){
				glPushMatrix();
				glTranslatef(i*10, 0, j*(-10));
				make_extra_points();
				glPopMatrix();
			}
		}
	}
        
}

void make_wall(){ // zidovi
	GLfloat ambient_coeffs_gray[] = {0,0,1,1};
	GLfloat diffuse_coeffs_gray[] = {0.6117,0.2196,0.0509,1};
	GLfloat specular_coeffs[] = { 0, 0, 0, 1 };
    	GLfloat shininess = 0;
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs_gray);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs_gray);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
    	glMaterialf(GL_FRONT, GL_SHININESS, shininess);
	glutSolidCube(10);	
}
void make_character(){ // packman
	//animacija kretanja
	switch(move){
		case 1 : glTranslatef(x_coordinate*10 + animation_parameter, 0, z_coordinate*10); break;
		case 2 : glTranslatef(x_coordinate*10, 0, z_coordinate*10 + animation_parameter); break;
		case 3 : glTranslatef(x_coordinate*10 - animation_parameter, 0, z_coordinate*10); break;
		case 4 : glTranslatef(x_coordinate*10, 0, z_coordinate*10 - animation_parameter); break;
		default : glTranslatef(x_coordinate*10, 0, z_coordinate*10); break;
	}
	glRotatef(direction,0,1,0);
	glPushMatrix();
	if(bonus_time==0){ //menja boju u belo za bonus time
  		glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
  		GLfloat bodyColorA[] = {1.0f, 1.0f, 0.0f, 1.0f};
  		GLfloat bodyColorD[] = {0.7f, 0.7f, 0.0f, 1.0f};
  		GLfloat bodyColorE[] = {0.0f, 0.0f, 0.0f, 1.0f};
  		GLfloat bodyColorS[] = {1.0f, 1.0f, 0.0f, 1.0f};
  		glMaterialfv(GL_FRONT, GL_AMBIENT, bodyColorA);
  		glMaterialfv(GL_FRONT, GL_DIFFUSE, bodyColorD);
  		glMaterialfv(GL_FRONT, GL_EMISSION, bodyColorE);
  		glMaterialfv(GL_FRONT, GL_SPECULAR, bodyColorS);
  		glMaterialf(GL_FRONT, GL_SHININESS, 4);
	}
	else{
		glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
  		GLfloat bodyColorA[] = {0.0f, 0.0f, 1.0f, 1.0f};
  		GLfloat bodyColorD[] = {0.0f, 0.0f, 1.0f, 1.0f};
  		GLfloat bodyColorE[] = {0.0f, 0.0f, 0.0f, 1.0f};
  		GLfloat bodyColorS[] = {0.0f, 0.0f, 1.0f, 1.0f};
  		glMaterialfv(GL_FRONT, GL_AMBIENT, bodyColorA);
  		glMaterialfv(GL_FRONT, GL_DIFFUSE, bodyColorD);
  		glMaterialfv(GL_FRONT, GL_EMISSION, bodyColorE);
  		glMaterialfv(GL_FRONT, GL_SPECULAR, bodyColorS);
  		glMaterialf(GL_FRONT, GL_SHININESS, 4);	
	}

  	glutSolidSphere(5, 24, 24);
	glPopMatrix();
	//levo oko
	glPushMatrix();
		glTranslatef(-2, 3.5, 2); 
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		GLfloat eyebrowColor[] = {0.0f, 0.0f, 0.0f, 1.0f};
		glMaterialfv(GL_FRONT, GL_AMBIENT, eyebrowColor);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, eyebrowColor);
		glMaterialfv(GL_FRONT, GL_EMISSION, eyebrowColor);
		glMaterialfv(GL_FRONT, GL_SPECULAR, eyebrowColor);
		glMaterialf(GL_FRONT, GL_SHININESS, 5);		
		glutSolidSphere(1, 16, 16);
  	glPopMatrix();
	//desno oko
	glPushMatrix();
		glTranslatef(2, 3.5, 2); 
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		glMaterialfv(GL_FRONT, GL_AMBIENT, eyebrowColor);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, eyebrowColor);
		glMaterialfv(GL_FRONT, GL_EMISSION, eyebrowColor);
		glMaterialfv(GL_FRONT, GL_SPECULAR, eyebrowColor);
		glMaterialf(GL_FRONT, GL_SHININESS, 5);		
		glutSolidSphere(1, 16, 16);

  	glPopMatrix();
	//usta tj. jezik
	glPushMatrix();
		glRotatef(80,1,0,0);
		glScalef(1.5,1.5,1);
		glTranslatef(0, 1.3, -0.6); 
		glColor4f(0.5098f, 0.0f, 0.0f, 1.0f);
		GLfloat tongueColor[] = {0.5098f, 0.0f, 0.0f, 1.0f};
		glMaterialfv(GL_FRONT, GL_AMBIENT, tongueColor);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, tongueColor);
		//glMaterialfv(GL_FRONT, GL_EMISSION, tongueColor);
		glMaterialfv(GL_FRONT, GL_SPECULAR, tongueColor);
		glMaterialf(GL_FRONT, GL_SHININESS, 5);		
		glutSolidTorus(1,1.3,20,20);
  	glPopMatrix();
}
void make_points(){ //obicni poeni
	glPushMatrix();
		glScalef(2,2,2);
		glColor4f(1.0f, 0.65f, 0.3f, 1.0f);
		GLfloat pointColor[] = {1.0f, 0.65f, 0.3f, 1.0f};
		glMaterialfv(GL_FRONT, GL_AMBIENT, pointColor);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, pointColor);
		//glMaterialfv(GL_FRONT, GL_EMISSION, pointColor);
		glMaterialfv(GL_FRONT, GL_SPECULAR, pointColor);
		glMaterialf(GL_FRONT, GL_SHININESS, 5);		
		glutSolidOctahedron();

  	glPopMatrix();	
}
void make_extra_points(){
	glPushMatrix();
		glScalef(2,2,2);
		glColor4f(0.0f, 0.6f, 0.2f, 1.0f);//zelena
		GLfloat extraPointColor[] = {0.0f, 0.6f, 0.2f, 1.0f};
		glMaterialfv(GL_FRONT, GL_AMBIENT, extraPointColor);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, extraPointColor);
		//glMaterialfv(GL_FRONT, GL_EMISSION, extraPointColor);
		glMaterialfv(GL_FRONT, GL_SPECULAR, extraPointColor);
		glMaterialf(GL_FRONT, GL_SHININESS, 5);		
		glutSolidDodecahedron();
  	glPopMatrix();
}
void make_ghosts(int p){
	glScalef(1,2,1);
	if(p==6){	//PURPLE GHOST
		glPushMatrix();
		//if(!purple_eaten){	
		//animacija kretanja
		//if(!pause)
		switch(move_purple_ghost){
			case 1 : glTranslatef(ghost_purple_x*10 + animation_ghost_parameter, 0, ghost_purple_z*10); break;
			case 2 : glTranslatef(ghost_purple_x*10, 0, ghost_purple_z*10 + animation_ghost_parameter); break;
			case 3 : glTranslatef(ghost_purple_x*10 - animation_ghost_parameter, 0, ghost_purple_z*10); break;
			case 4 : glTranslatef(ghost_purple_x*10, 0, ghost_purple_z*10 - animation_ghost_parameter); break;
			default : glTranslatef(ghost_purple_x*10, 0, ghost_purple_z*10); break;
		}
		glRotatef(direction_purple_ghost,0,1,0);
		//}
		if(bonus_time){ // menja boje u bonus time
			bonus_ghost_color();	
		}
		else{	            
			glColor4f(0.8f, 0.0f, 0.8f, 1.0f);//ljubicasta
			GLfloat ghostColor1[] = {0.8f, 0.0f, 0.8f, 1.0f}; 			
			glMaterialfv(GL_FRONT, GL_AMBIENT, ghostColor1);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, ghostColor1);
			glMaterialfv(GL_FRONT, GL_SPECULAR, ghostColor1);
			glMaterialf(GL_FRONT, GL_SHININESS, 5);	
		}	
		glutSolidCube(6);
		//oci	
		make_ghost_eyes();

	  	glPopMatrix();
	}
	if(p==7){  	//PINK GHOST
		glPushMatrix();	
		//if(!pink_eaten){
		switch(move_pink_ghost){
			case 1 : glTranslatef(ghost_pink_x*10 + animation_ghost_parameter, 0, ghost_pink_z*10); break;
			case 2 : glTranslatef(ghost_pink_x*10, 0, ghost_pink_z*10 + animation_ghost_parameter); break;
			case 3 : glTranslatef(ghost_pink_x*10 - animation_ghost_parameter, 0, ghost_pink_z*10); break;
			case 4 : glTranslatef(ghost_pink_x*10, 0, ghost_pink_z*10 - animation_ghost_parameter); break;
			default : glTranslatef(ghost_pink_x*10, 0, ghost_pink_z*10); break;
		}
		glRotatef(direction_pink_ghost,0,1,0);
		//}
		if(bonus_time){
			bonus_ghost_color();	
		}
		else{	            
			glColor4f(1.0f, 0.6f, 1.0f, 1.0f);//roze
			GLfloat ghostColor2[] = {1.0f, 0.6f, 1.0f, 1.0f}; 			
			glMaterialfv(GL_FRONT, GL_AMBIENT, ghostColor2);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, ghostColor2);
			glMaterialfv(GL_FRONT, GL_SPECULAR, ghostColor2);
			glMaterialf(GL_FRONT, GL_SHININESS, 5);	
		}		
		glutSolidCube(6);
	
		make_ghost_eyes();

		glPopMatrix();
	}
	if(p==5){	//LIGHT BLUE GHOST
		glPushMatrix();
		//if(!lightblue_eaten){
		switch(move_lightblue_ghost){
			case 1 : glTranslatef(ghost_lightblue_x*10 + animation_ghost_parameter, 0, ghost_lightblue_z*10); break;
			case 2 : glTranslatef(ghost_lightblue_x*10, 0, ghost_lightblue_z*10 + animation_ghost_parameter); break;
			case 3 : glTranslatef(ghost_lightblue_x*10 - animation_ghost_parameter, 0, ghost_lightblue_z*10); break;
			case 4 : glTranslatef(ghost_lightblue_x*10, 0, ghost_lightblue_z*10 - animation_ghost_parameter); break;
			default : glTranslatef(ghost_lightblue_x*10, 0, ghost_lightblue_z*10); break;
		}
		glRotatef(direction_lightblue_ghost,0,1,0);
		//}
		if(bonus_time){
			bonus_ghost_color();	
		}
		else{	            
			glColor4f(0.0f, 1.0f, 1.0f, 1.0f);//svetlo plava
			GLfloat ghostColor3[] = {0.0f, 1.0f, 1.0f, 1.0f};			
			glMaterialfv(GL_FRONT, GL_AMBIENT, ghostColor3);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, ghostColor3);
			glMaterialfv(GL_FRONT, GL_SPECULAR, ghostColor3);
			glMaterialf(GL_FRONT, GL_SHININESS, 5);	
		}		            
		
		glutSolidCube(6);
	
		make_ghost_eyes();

		glPopMatrix();
	}
	if(p==4){ 	//BLUE GHOST
		glPushMatrix()	;
		//if(!blue_eaten){
		switch(move_blue_ghost){
			case 1 : glTranslatef(ghost_blue_x*10 + animation_ghost_parameter, 0, ghost_blue_z*10); break;
			case 2 : glTranslatef(ghost_blue_x*10, 0, ghost_blue_z*10 + animation_ghost_parameter); break;
			case 3 : glTranslatef(ghost_blue_x*10 - animation_ghost_parameter, 0, ghost_blue_z*10); break;
			case 4 : glTranslatef(ghost_blue_x*10, 0, ghost_blue_z*10 - animation_ghost_parameter); break;
			default : glTranslatef(ghost_blue_x*10, 0, ghost_blue_z*10); break;
		}
		glRotatef(direction_blue_ghost,0,1,0);
		//}		    
		if(bonus_time){
			bonus_ghost_color();	
		}
		else{	            
			glColor4f(0.0f, 0.0f, 1.0f, 1.0f);//plava
			GLfloat ghostColor4[] = {0.0f, 0.0f, 1.0f, 1.0f}; 			
			glMaterialfv(GL_FRONT, GL_AMBIENT, ghostColor4);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, ghostColor4);
			glMaterialfv(GL_FRONT, GL_SPECULAR, ghostColor4);
			glMaterialf(GL_FRONT, GL_SHININESS, 5);	
		}	
		glutSolidCube(6);
	
		make_ghost_eyes();
	
		glPopMatrix();
	}
 
}
void bonus_ghost_color(){
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);//bela
			GLfloat ghostColor4[] = {1.0f, 1.0f, 1.0f, 1.0f};
			glMaterialfv(GL_FRONT, GL_AMBIENT, ghostColor4);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, ghostColor4);
			glMaterialfv(GL_FRONT, GL_SPECULAR, ghostColor4);
			glMaterialf(GL_FRONT, GL_SHININESS, 5);	
  
}
void make_ghost_eyes(){ //oci kod botova
	glTranslatef(2, 3.5, 3); 
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		GLfloat eyeGhostColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
		glMaterialfv(GL_FRONT, GL_AMBIENT, eyeGhostColor);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, eyeGhostColor);
		//glMaterialfv(GL_FRONT, GL_EMISSION, eyeGhostColor);
		glMaterialfv(GL_FRONT, GL_SPECULAR, eyeGhostColor);
		glMaterialf(GL_FRONT, GL_SHININESS, 5);		
		glutSolidSphere(1, 16, 16);

		glTranslatef(-4, 0, 0); 
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		//GLfloat eyeGhostColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
		glMaterialfv(GL_FRONT, GL_AMBIENT, eyeGhostColor);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, eyeGhostColor);
		//glMaterialfv(GL_FRONT, GL_EMISSION, eyeGhostColor);
		glMaterialfv(GL_FRONT, GL_SPECULAR, eyeGhostColor);
		glMaterialf(GL_FRONT, GL_SHININESS, 5);		
		glutSolidSphere(1, 16, 16);
}
void scoreboard() {
	glPushMatrix();
	glTranslatef(120,0,-240);
	glScalef(0.05, 0.05, 0.05);
	char pom1[]="Pause 'P'";
	int j=0;	
	for (; pom1[j] != '\0'; j++ ) {
      		glutStrokeCharacter(GLUT_STROKE_ROMAN, pom1[j]);
	}
	glPopMatrix();
	glPushMatrix();
	glTranslatef(120,0,-230);
	glScalef(0.05, 0.05, 0.05);
	char pom2[]="Lost LIFE,press 'P'";
	int k=0;
	for (; pom2[k] != '\0'; k++ ) {
      		glutStrokeCharacter(GLUT_STROKE_ROMAN, pom2[k]);
	}
	glPopMatrix();

	
	char pom[]="Score:";
	char str[10];

	sprintf(str, "%d", score);
	strcat(pom,str);
	
	glPushMatrix();
	glTranslatef(-85,0,-240);
	glScalef(0.1, 0.1, 0.1);
	int i;	
	for ( i = 0; pom[i] != '\0'; i++ ) {
      		glutStrokeCharacter(GLUT_STROKE_ROMAN, pom[i]);
	}
	glPopMatrix();
	
	char pom3[]="Life:";
	char str2[10];

	sprintf(str2, "%d", life);
	strcat(pom3,str2);
	
	glPushMatrix();
	glTranslatef(-80,0,-220);
	glScalef(0.1, 0.1, 0.1);
	int m;	
	for ( m = 0; pom3[m] != '\0'; m++ ) {
      		glutStrokeCharacter(GLUT_STROKE_ROMAN, pom3[m]);
	}
	glPopMatrix();
}
