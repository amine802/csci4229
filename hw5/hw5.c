/*
 * Simple program that builds a House like object and puts them together
 * to form a cool object. There is also a light that spins around allowing
 * demonstrating how light affects the scene differently
 * This was made using code from ex13.c and my Hw4
 */

#include "CSCIx229.h"

/*  Global Variables  */
int th=0;       // Azimuth of view angle
int ph=0;       // Elevation of view angle
int mode=0;     // Dimension (1-4)
double dim=10;   // Dimension of orthogonal box
char* text[] = {"3D"};  // Dimension display text
int fov=55;       //  Field of view (for perspective)		<---- Taken from ex9.c
double asp=1;     //  Aspect ratio 				<---- Taken from ex9.c
int light=1;
int move=1;
//double dim=5.0;   //  Size of world				<---- Taken from ex9.c

int piece1 = 1;	// Variables to turn on display for each of the objects
int piece2 = 1;
int piece3 = 1;
int piece4 = 1;
int piece5 = 1;
int piece6 = 1;

int one       =   1;  // Unit value         <---- All these variables taken from ex13.c
int distance  =  10;  // Light Distance     
int inc       =  10;  // Ball increment     
int smooth    =   1;  // Smooth/Flat shading
int local     =   0;  // Local Viewer Model
int emission  =   0;  // Emission intensity (%)
int ambient   =  30;  // Ambient intensity (%)
int diffuse   = 100;  // Diffuse intensity (%)
int specular  =   0;  // Specular intensity (%)
int shininess =   0;  // Shininess (power of two)
float shiny   =   1;  // Shininess (value)
int zh        =  90;  // Light azimuth
float ylight  =   0;  // Elevation of light




void bottom(){         //Builds bottom of the piece
  glBegin(GL_QUADS);

  glColor3ub(255,0,0);
  glNormal3f( 0, -1, 0);
  glVertex3f(-1, -4, 1);
  glVertex3f(1, -4, 1);
  glVertex3f(1, -4, -1);
  glVertex3f(-1, -4, -1);

  glEnd();

  // glBegin(GL_TRIANGLES);       Experimenting with a different shape here. Will implement another time

  // glColor3ub(255, 0, 0);
  // glNormal3f( 0, 0, 0);
  // glVertex3f(1, -4, 1);
  // glVertex3f(0, -5, 0);
  // glVertex3f(-1, -4, 1);

  // glEnd();
  
  // glBegin(GL_LINE_LOOP);

  // glColor3ub(221, 194, 59); //Outline one roof
  // glVertex3f(1, -4, 1);
  // glVertex3f(0, -5, 0);
  // glVertex3f(-1, -4, 1);

  // glEnd();

  }
  
void wall(){          //Makes one rectangular wall
  glBegin(GL_QUADS);

  glColor3ub(255,255,255);
  glNormal3f( 0, 0, 1);
  glVertex3f(-1, -4, 1);
  glVertex3f(1, -4, 1);
  glVertex3f(1, -1, 1);
  glVertex3f(-1, -1, 1);

  glEnd();
  
  glBegin(GL_LINE_LOOP);    // Outline on wall
  
  glColor3ub(221, 194, 59);
  glVertex3f(-1, -4, 1);
  glVertex3f(1, -4, 1);
  glVertex3f(1, -1, 1);
  glVertex3f(-1, -1, 1);
  
  glEnd();
  }
  
void roof(){          //Makes roof section for that piece of wall
  glBegin(GL_TRIANGLES);

  glColor3ub(255, 0, 0);
  glNormal3f( 0, 2, 2);
  glVertex3f(1, -1, 1);
  glVertex3f(0, 0, 0);
  glVertex3f(-1, -1, 1);

  glEnd();
  
  glBegin(GL_LINE_LOOP);

  glColor3ub(221, 194, 59); //Outline one roof
  glVertex3f(1, -1, 1);
  glVertex3f(0, 0, 0);
  glVertex3f(-1, -1, 1);

  glEnd();
  }
  
void house(){         //Builds part with 4 walls, a bottom, and a roof
  glPushMatrix();
  bottom();
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

static void Vertex(double th,double ph)       //<-- Taken from ex13.c
{
   double x = Sin(th)*Cos(ph);
   double y = Cos(th)*Cos(ph);
   double z =         Sin(ph);
   //  For a sphere at the origin, the position
   //  and normal vectors are the same
   glNormal3d(x,y,z);
   glVertex3d(x,y,z);
}

static void ball(double x,double y,double z,double r)       //<-- Taken from ex13.c
{
   int th,ph;
   float yellow[] = {1.0,1.0,0.0,1.0};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glScaled(r,r,r);
   //  White ball
   glColor3f(1,1,1);
   glMaterialf(GL_FRONT,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
   glMaterialfv(GL_FRONT,GL_EMISSION,Emission);
   //  Bands of latitude
   for (ph=-90;ph<90;ph+=inc)
   {
      glBegin(GL_QUAD_STRIP);
      for (th=0;th<=360;th+=2*inc)
      {
         Vertex(th,ph);
         Vertex(th,ph+inc);
      }
      glEnd();
   }
   //  Undo transofrmations
   glPopMatrix();
}

void idle()                                 //What glut does when user isn't inputting anything
{
   //  Elapsed time in seconds
   double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;        
   zh = fmod(90*t,360.0);                             //Modifies the position of the light ball
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

void key(unsigned char ch,int x,int y)
{
  
   // Reset Everything
   if (ch == '0'){
      th = ph = 0;
      piece1 = piece2 = piece3 = piece4 = piece5 = piece6 =  1;
   }
   //  Modify which houses are visible
   else if (ch == '1'){ 
	   if(piece1 == 0){ piece1 = 1;}
	   else{ piece1 = 0;}
   }
   else if (ch == '2'){ 
	   if(piece2 == 0){ piece2 = 1;}
	   else{ piece2 = 0;}
   }
   else if (ch == '3'){ 
	   if(piece3 == 0){ piece3 = 1;}
	   else{ piece3 = 0;}
   }
   else if (ch == '4'){ 
	   if(piece4 == 0){ piece4 = 1;}
	   else{ piece4 = 0;}
   }
   else if (ch == '5'){ 
	   if(piece5 == 0){ piece5 = 1;}
	   else{ piece5 = 0;}
   }
   else if (ch == '6'){ 
	   if(piece6 == 0){ piece6 = 1;}
	   else{ piece6 = 0;}
   }
   else if (ch == 'z' && dim > 1){
   		dim -= 0.1;
   }
   else if (ch == 'Z' ){
   		dim += 0.1;
   }
   else if (ch == 'm' || ch == 'M'){
   		mode = 1-mode;
   }
   else if (ch == '-' && ch>1){
   		fov--;
   }
   else if (ch == '+' && ch<179){
   		fov++;
   }
   else if (ch == 'l' || ch == 'L'){
      light = 1-light;
   }
   else if (ch=='['){
      ylight -= 0.1;
    }
   else if (ch==']'){
      ylight += 0.1;
    }
   else if (ch=='a' && ambient>0){
      ambient -= 5;
    }
   else if (ch=='A' && ambient<100){
      ambient += 5;
    }
    else if (ch=='d' && diffuse>0){
      diffuse -= 5;
   }
   else if (ch=='D' && diffuse<100){
      diffuse += 5;
    }
   else if (ch=='s' && specular>0){
      specular -= 5;
    }
   else if (ch=='S' && specular<100){
      specular += 5;
    }
   else if (ch=='e' && emission>0){
      emission -= 5;
    }
   else if (ch=='E' && emission<100){
      emission += 5;
    }
   else if (ch=='n' && shininess>-1){
      shininess -= 1;
    }
   else if (ch=='N' && shininess<7){
      shininess += 1;
    }
   else if (ch == 'r' || ch == 'R'){
      move = 1-move;
    }
   else if (ch == 27){
		exit(0);
   }
   shiny = shininess<0 ? 0 : pow(2.0,shininess);
   Project(mode?fov:0,asp,dim);
   glutIdleFunc(move?idle:NULL);
   //  Redisplay
   glutPostRedisplay();
}


void display()
{
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);   //Clear Everything
  glEnable(GL_DEPTH_TEST);
  glLoadIdentity();

  if (mode)                                           //Changes world orientation from orthogonal to perspective
   {
      double Ex = -2*dim*Sin(th)*Cos(ph);
      double Ey = +2*dim        *Sin(ph);
      double Ez = +2*dim*Cos(th)*Cos(ph);
      gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);
   }
   else                                               //Orthogonal orientation
   {
      glRotatef(ph,1,0,0);
      glRotatef(th,0,1,0);
   }
  
   glShadeModel(smooth ? GL_SMOOTH : GL_FLAT);

  if (light){                                     // <---- Taken from ex13.c/ How the program projects light with the ball
        //  Translate intensity to color vectors
        float Ambient[]   = {0.01*ambient ,0.01*ambient ,0.01*ambient ,1.0};
        float Diffuse[]   = {0.01*diffuse ,0.01*diffuse ,0.01*diffuse ,1.0};
        float Specular[]  = {0.01*specular,0.01*specular,0.01*specular,1.0};
        //  Light position
        float Position[]  = {distance*Cos(zh),ylight,distance*Sin(zh),1.0};
        //  Draw light position as ball (still no lighting here)
        glColor3f(1,1,1);
        ball(Position[0],Position[1],Position[2] , 0.1);
        //  OpenGL should normalize normal vectors
        glEnable(GL_NORMALIZE);
        //  Enable lighting
        glEnable(GL_LIGHTING);
        //  Location of viewer for specular calculations
        glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,local);
        //  glColor sets ambient and diffuse color materials
        glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
        glEnable(GL_COLOR_MATERIAL);
        //  Enable light 0
        glEnable(GL_LIGHT0);
        //  Set ambient, diffuse, specular components and position of light 0
        glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
        glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
        glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
        glLightfv(GL_LIGHT0,GL_POSITION,Position);
   }
   else{                                        //Disables lighting
    glDisable(GL_LIGHTING);
   }

  if(piece1 == 1){		// If statements determine whether a piece is displayed or not
	house();
  }
  if(piece2 == 1){
	glPushMatrix();
	glRotated(180, 1, 0, 0);
	house();
	glPopMatrix();
  }
  if(piece3 == 1){
	glPushMatrix();
	glRotated(90, 1, 0, 0);
	house();
	glPopMatrix();
  }
  if(piece4 == 1){
	glPushMatrix();
	glRotated(90, -1, 0, 0);
	house();
	glPopMatrix();
  }
  if(piece5 == 1){
	glPushMatrix();
	glRotated(90, 0, 0, 1);
	house();
	glPopMatrix();
  }
  if(piece6 == 1){
	glPushMatrix();
	glRotated(90, 0, 0, -1);
	house();
	glPopMatrix();
  }  

  glDisable(GL_LIGHTING);

  glWindowPos2i(5,5);
  Print("Angle=%d,%d  Dim=%.1f FOV=%d Projection=%s Light=%s",                    //Taken from ex13.c
     th,ph,dim,fov,mode?"Perpective":"Orthogonal",light?"On":"Off");
   if (light)
   {
      glWindowPos2i(5,45);
      Print("Model=%s LocalViewer=%s Distance=%d Elevation=%.1f",smooth?"Smooth":"Flat",local?"On":"Off",distance,ylight);
      glWindowPos2i(5,25);
      Print("Ambient=%d  Diffuse=%d Specular=%d Emission=%d Shininess=%.0f",ambient,diffuse,specular,emission,shiny);
   }

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
    //  Smooth color model
   else if (key == GLUT_KEY_F1)
      smooth = 1-smooth;
   //  Keep angles to +/-360 degrees
   th %= 360;
   ph %= 360;

   Project(mode?fov:0,asp,dim);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when the window is resized <---- Also taken from ex6.c
 */

void reshape(int width,int height) {
	asp = (height>0) ? (double)width/height : 1;
   //  Set the viewport to the entire window
   glViewport(0,0, width,height);
   //  Set projection
   Project(mode?fov:0,asp,dim);	
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
   //  Request 750 x 750 pixel window
   glutInitWindowSize(750,750);
   //  Create the window
   glutCreateWindow("Sami Meharzi: HW 5");
   //  Tell GLUT to call "display" when the scene should be drawn
   glutDisplayFunc(display);
  //  Tell GLUT to call "reshape" when the window is resized
   glutReshapeFunc(reshape);
   //  Tell GLUT to call "special" when an arrow key is pressed
   glutSpecialFunc(special);
   //  Tell GLUT to call "key" when a key is pressed
   glutKeyboardFunc(key);
   //   Tell GLUT what to do when program is idle
   glutIdleFunc(idle);
   //  Pass control to GLUT so it can interact with the user
   ErrCheck("init");
   glutMainLoop();
   //  Return code
   return 0;
}
