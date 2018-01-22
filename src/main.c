#include <GL/glut.h>
#include "game.h"

void set_light();
void on_reshape(int width, int height);
void on_display(void);

int main(int argc, char **argv)
{	
	//Inicijalizacija
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(argv[0]);

	glClearColor(0.8549,0.9686,0.6509, 0);
	glEnable(GL_DEPTH_TEST);
	
	//time_t t;
	//srand(time(&t));

	set_light();	//postavljanje svetla
	set_begining(); // fja iz game.c , postavljaju onkeyboard,ondisplay...
	glutMainLoop();

	return 0;
}
void set_light()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	GLfloat light_position[]	= { 0.05, 0.3, 0.7, 0};
	GLfloat light_ambient[]		= { 0.1, 0.1, 0.1, 1 };
	GLfloat light_diffuse[]		= { 1, 1, 1, 1 };
	GLfloat light_specular[]	= { 1, 1, 1, 1 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);	
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	
	GLfloat shiness = 30;
	glMaterialf(GL_FRONT, GL_SHININESS, shiness);	
}
