/*
 * Simple program that builds a House like object and puts them together
 * to form a cool pattern
 */

//Libraries and Shit
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

/*  Global Variables  */
int th=0;       // Azimuth of view angle
int ph=0;       // Elevation of view angle
int mode=1;     // Dimension (1-4)
double dim=2;   // Dimension of orthogonal box
char* text[] = {"3D"};  // Dimension display text
int house1 = 1;	// Variables to turn on display for each of the objects
int house2 = 1;
int house3 = 1;
int house4 = 1;
int house5 = 1;
int house6 = 1;
int house7 = 1;

/*
 *  Convenience routine to output raster text <---- Taken from ex6.c
 *  Use VARARGS to make this more flexible
 */
#define LEN 8192  // Maximum length of text string
void Print(const char* format , ...)
{
	 char    buf[LEN];
	 char*   ch=buf;
	va_list args;
	   //  Turn the parameters into a character string
	   va_start(args,format);
	   vsnprintf(buf,LEN,format,args);
	   va_end(args);
	   //  Display the characters one at a time at the current raster position
	   while (*ch)
		  glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*ch++);
}

void key(unsigned char ch,int x,int y)
{
  
   // Reset Everything
   if (ch == '0'){
      th = ph = 0;
      house1 = house2 = house3 = house4 = house5 = house6 = house7 = 1;
   }
   //  Modify which houses are visible
   else if (ch == '1'){ 
	   if(house1 == 0){ house1 = 1;}
	   else{ house1 = 0;}
   }
   else if (ch == '2'){ 
	   if(house2 == 0){ house2 = 1;}
	   else{ house2 = 0;}
   }
   else if (ch == '3'){ 
	   if(house3 == 0){ house3 = 1;}
	   else{ house3 = 0;}
   }
   else if (ch == '4'){ 
	   if(house4 == 0){ house4 = 1;}
	   else{ house4 = 0;}
   }
   else if (ch == '5'){ 
	   if(house5 == 0){ house5 = 1;}
	   else{ house5 = 0;}
   }
   else if (ch == '6'){ 
	   if(house6 == 0){ house6 = 1;}
	   else{ house6 = 0;}
   }
   else if (ch == '7'){ 
	   if(house7 == 0){ house7 = 1;}
	   else{ house7 = 0;}
   }
   else if (ch == 27){
		exit(0);
   }
  
   //  Redisplay
   glutPostRedisplay();
}

void Floor(){					//Builds House floor
	glBegin(GL_QUADS);

	glColor3ub(0,0,255);
	glVertex3f(-1, -4.1, 1);
	glVertex3f(1, -4.1, 1);
	glVertex3f(1, -4.1, -1);
	glVertex3f(-1, -4.1, -1);

	glEnd();
	}
	
	
void wall(){					//Makes one square wall
	glBegin(GL_QUADS);

	glColor3ub(0,0,255);
	glVertex3f(-1, -4, 1);e
	glVertex3f(1, -4, 1);
	glVertex3f(1, -1, 1);
	glVertex3f(-1, -1, 1);

	glEnd();
	
	glBegin(GL_LINE_LOOP);		// Outline on wall
	
	glColor3ub(255,20,147);
	glVertex3f(-1, -4, 1);
	glVertex3f(1, -4, 1);
	glVertex3f(1, -1, 1);
	glVertex3f(-1, -1, 1);
	
	glEnd();
	}
	
void roof(){					//Makes roof section for that piece of wall
	glBegin(GL_TRIANGLES);

	glColor3ub(0, 0, 255);
	glVertex3f(1, -1, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(-1, -1, 1);

	glEnd();
	
	glBegin(GL_LINE_LOOP);

	glColor3ub(255, 255, 255);	//Outline one roof
	glVertex3f(1, -1, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(-1, -1, 1);

	glEnd();
	}
	
void house(){					//Builds House with 4 walls, a floor, and a roof
	glPushMatrix();
	Floor();
	wall();
	roof();
	glRotated(90, 0, 1, 0);
	wall();
	roof();
	glRotated(90, 0, 1, 0);
	wall();
	roof();
	glRotated(90, 0, 1, 0);
	wall();
	roof();
	glPopMatrix();
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);   //Clear Everything
  glEnable(GL_DEPTH_TEST);
  glLoadIdentity();
  glOrtho(-5, 5, -5, 5, -10, 10);

  glRotated(ph,1,0,0); // Initial view angle
  glRotated(th,0,1,0); 
  
  if(house1 == 1){		// If statements determine whether a house is displayed or not
	house();
  }
  if(house2 == 1){
	glPushMatrix();
	glRotated(180, 1, 0, 0);
	house();
	glPopMatrix();
  }
  if(house3 == 1){
	glPushMatrix();
	glRotated(90, 1, 0, 0);
	house();
	glPopMatrix();
  }
  if(house4 == 1){
	glPushMatrix();
	glRotated(90, -1, 0, 0);
	house();
	glPopMatrix();
  }
  if(house5 == 1){
	glPushMatrix();
	glRotated(90, 0, 0, 1);
	house();
	glPopMatrix();
  }
  if(house6 == 1){
	glPushMatrix();
	glRotated(90, 0, 0, -1);
	house();
	glPopMatrix();
  }
  
  if(house7 == 1){
	glPushMatrix();
	glTranslated(5, 0, 5);
	glScaled(1.5, 1, 1.5);
	house();
	glPopMatrix();
  }
  
  
  glWindowPos2i(5,5);
  Print("View Angle=%d,%d\n",th,ph);    //  Display View angles
  glFlush();
  glutSwapBuffers();    
}


/* 
 * What happens different things are pressed <---- Also taken from ex6.c
 */
void special(int key,int x,int y)
{
   //  Right arrow key - increase angle by 5 degrees
   if (key == GLUT_KEY_RIGHT)
      th += 5;
   //  Left arrow key - decrease angle by 5 degrees
   else if (key == GLUT_KEY_LEFT)
      th -= 5;
   //  Up arrow key - increase elevation by 5 degrees
   else if (key == GLUT_KEY_UP)
      ph += 5;
   //  Down arrow key - decrease elevation by 5 degrees
   else if (key == GLUT_KEY_DOWN)
      ph -= 5;
   //  Keep angles to +/-360 degrees
   th %= 360;
   ph %= 360;
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when the window is resized <---- Also taken from ex6.c
 */

void reshape(int width,int height) 
{
   //  Ratio of the width to the height of the window
   double w2h = (height>0) ? (double)width/height : 1;
   //  Set the viewport to the entire window
   glViewport(0,0, width,height);
   //  Tell OpenGL we want to manipulate the projection matrix
   glMatrixMode(GL_PROJECTION);
   //  Undo previous transformations
   glLoadIdentity();
   //  Orthogonal projection box adjusted for the
   //  aspect ratio of the window
   glOrtho(-dim*w2h,+dim*w2h, -dim,+dim, -dim,+dim);
   //  Switch to manipulating the model matrix
   glMatrixMode(GL_MODELVIEW);
   //  Undo previous transformations
   glLoadIdentity();
}

/*
 *  Start up GLUT and tell it what to do <---- Also taken from ex6.c
 */
int main(int argc,char* argv[])
{
  //  Initialize GLUT and process user parameters
   glutInit(&argc,argv);
   //  Request double buffered, true color window 
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   //  Request 500 x 500 pixel window
   glutInitWindowSize(750,750);
   //  Create the window
   glutCreateWindow("Sami Meharzi: HW 3");
   //  Tell GLUT to call "display" when the scene should be drawn
   glutDisplayFunc(display);
  //  Tell GLUT to call "reshape" when the window is resized
   glutReshapeFunc(reshape);
   //  Tell GLUT to call "special" when an arrow key is pressed
   glutSpecialFunc(special);
   //  Tell GLUT to call "key" when a key is pressed
   glutKeyboardFunc(key);
   //  Pass control to GLUT so it can interact with the user
   glutMainLoop();
   //  Return code
   return 0;
}
