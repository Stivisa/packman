#include "txloader.h"
//POZAJMIO SA INTERNETA DA BIH UCITAO .bmp SLIKE
int w,h;

char *img_read(char * name){

	FILE *f = fopen(name,"rb");
	if(f == NULL) exit(0);
	int of;
	fseek(f, 10, SEEK_SET);
	fread(&of, sizeof(int), 1, f);
	fseek(f, 4, SEEK_CUR);
	fread(&w, sizeof(int), 1, f);
	fread(&h, sizeof(int), 1, f);

	fseek(f, of, SEEK_SET);
	
	//char c;
	//int j = 0;
	int by = ((w * 3 + 3)/4) * 4 - (w * 3 % 4);
	char *tmp_m = malloc(sizeof(char) * by * h);
	char *m = malloc(sizeof(char) * w * h * 3);
	fread(tmp_m, sizeof(char) * by * h, 1, f);
	int x,y,i;	
	for(y = 0; y < h; y++){
		for(x = 0; x < w; x++){
			for(i = 0; i < 3; i++){
				m[3*(w*y + x) + i] = tmp_m[3*(w*y + x) + (2 - i)];			
			}
		}	
	}
	free(tmp_m);
	return m;
}

GLuint loadTex(char *c){
	char *wa = img_read(c);
	GLuint texid;
	glGenTextures(1, &texid);
	glBindTexture(GL_TEXTURE_2D, texid);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, wa);
	free(wa);
	return texid;
}
void banner(GLuint tx){

	glEnable(GL_TEXTURE_2D);	
	glBindTexture(GL_TEXTURE_2D, tx);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glPushMatrix();
	glScalef(2,1,2);
	glTranslatef(-25,0,-10);

	glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
  		GLfloat tcA[] = {4.0f, 4.0f, 4.0f, 0.0f};
  		GLfloat tcD[] = {1.0f, 1.0f, 1.0f, 1.0f};
  		//GLfloat tcE[] = {0.1f, 0.1f, 0.1f, 1.0f};
  		GLfloat tcS[] = {1.0f, 1.0f, 1.0f, 1.0f};
  		glMaterialfv(GL_FRONT, GL_AMBIENT, tcA);
  		glMaterialfv(GL_FRONT, GL_DIFFUSE, tcD);
  		//glMaterialfv(GL_FRONT, GL_EMISSION, tcE);
  		glMaterialfv(GL_FRONT, GL_SPECULAR, tcS);
  		glMaterialf(GL_FRONT, GL_SHININESS, 4);

	glBegin(GL_QUADS);
	glColor4f(1.0, 1.0, 1.0,1.5);
	glTexCoord2f(1.0,1.0);
	glVertex3f(100, 10, -100);
	glTexCoord2f(0.0,1.0);
	glVertex3f(0, 10, -100);
	glTexCoord2f(0.0,0.0);
	glVertex3f(0, 10, 0);
	glTexCoord2f(1.0,0.0);
	glVertex3f(100, 10, 0);
	glEnd();
	
	/*
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(0, 50, 0);
	glTexCoord2f(0, 1); glVertex3f(0, 50, -100);
	glTexCoord2f(1, 1); glVertex3f(100, 50, -100);
	glTexCoord2f(1, 0); glVertex3f(100, 50, 0);
	glEnd();
	*/
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}
