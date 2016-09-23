/*
 * Simple program to demonstrate generating coordinates
 * using the Lorenz Attractor
 * 
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

/*  Lorenz Parameters/Globsl Variables  */
double s  = 10;
double b  = 2.6666;
double r  = 28;
int th=0;       // Azimuth of view angle
int ph=0;       // Elevation of view angle
int mode=1;     // Dimension (1-4)
double z=0;     // Z variable
double w=1;     // W variable
double dim=2;   // Dimension of orthogonal box
char* text[] = {"3D"};  // Dimension display text

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
      s = 10;
      b = 2.666666;
      r = 28;
   }
   //  Modify Lorenz Variables
   else if (ch == 's'){ s -= 1; }

   else if (ch == 'S'){ s += 1; }

   else if (ch == 'b'){ b -= .1; }

   else if (ch == 'B'){ b += .1; }

   else if (ch == 'r'){ r -= 1; }

   else if (ch == 'R'){ r += 1; }

   //  Redisplay
   glutPostRedisplay();
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT);   //Clear Everything
  glLoadIdentity();
  glOrtho(-1, 1, -1, 1, -10, 10);

  glRotated(ph,1,0,0); // Initial view angle
  glRotated(th,0,1,0);

  glBegin(GL_LINE_STRIP);

  //Moved Lorenz code from original main function to here.
  int i;
    
  double x = 1;
  double y = 1;
  double z = 1;
 
  double dt = .001;

  for (i = 0; i < 50000; i++) {            
      double dx = s*(y-x);
      double dy = x*(r-z) - y;
      double dz = x*y - b*z;

      x += dt*dx;
      y += dt*dy;
      z += dt*dz;        
	  
	  // Mess with colors
	  if (i%10 == 0){
		  glColor3ub(218, 165, 32);
	  }
	  else {
		  glColor3ub(139, 0, 0);
	  }
      
      // Multiply by .04 to make attractor fit in default view <--found on github 'https://github.com/dmurtari/csci4229/blob/master/hw2/lorenzfinal.c'
      glVertex4f(x*.04, y*.04, z*.04, w); 
    }


    glEnd();
    
    //  Draw and label axes
    glColor3f(1,1,1);
    glBegin(GL_LINES);
    glVertex3d(0,0,0);
    glVertex3d(1,0,0);
    glVertex3d(0,0,0);
    glVertex3d(0,1,0);
    glVertex3d(0,0,0);
    glVertex3d(0,0,1);
    glEnd();
    
    glRasterPos3d(1,0,0);
    Print("X");
    glRasterPos3d(0,1,0);
    Print("Y");
    glRasterPos3d(0,0,1);
    Print("Z");
    
    //  Display View angles
    glWindowPos2i(5,5);
    Print("View Angle=%d,%d",th,ph);
    
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
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
   //  Request 500 x 500 pixel window
   glutInitWindowSize(500,500);
   //  Create the window
   glutCreateWindow("Sami Meharzi: HW 2");
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
