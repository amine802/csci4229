#include "CSCIx229.h"

/*  Global Variables  */
double dim=5;   // Dimension of orthogonal box
double asp=1;     //  Aspect ratio 				<---- Taken from ex9.c
unsigned int texture[4];    //  Array to store different pictures/textures
int textMode = 0;     // Variable that determines which picture is going to be used
int whiteSpace[2];   // Blank Tile location
int moves = 0;      // Total number of player moves

struct Tile {         // Game Tile. Integers represent location of the tile
  int left;           // while floats represent the part of the image (texture) is on it
  int bottom;
  float textLeft;
  float textBottom;
};

struct Tile Tiles[4][4];      // Matrix where all the game tiles are stored including one white one.

void drawTile(int left, int bottom, float textX, float textY){
  if(textX == -1 || textY == -1){                     // Draw white tile
    glBegin(GL_QUADS);
    
      glColor3ub(255,255,255);
      glVertex2f(left, bottom); 
      glVertex2f(left+1, bottom); 
      glVertex2f(left+1, bottom+1); 
      glVertex2f(left, bottom+1); 

    glEnd();
  }
  else{                                                // Draw all the other tiles
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , textMode?GL_REPLACE:GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D,texture[textMode]);
    glColor3f(255,255,255);

    glBegin(GL_QUADS);

      glTexCoord2f(textX, textY);  glVertex2f(left, bottom); 
      glTexCoord2f(textX + 0.25, textY);  glVertex2f(left+1, bottom); 
      glTexCoord2f(textX+0.25, textY+0.25);  glVertex2f(left+1, bottom+1); 
      glTexCoord2f(textX, textY+0.25);  glVertex2f(left, bottom+1); 

    glEnd();
    glDisable(GL_TEXTURE_2D);
  }
}

void frame(){                     // Draws Gray frame around tiles
  glBegin(GL_QUADS);

    glColor3ub(192, 192, 192);
    //glNormal3f();
    glVertex2f(-0.5, -0.5);
    glVertex2f(0, 0);
    glVertex2f(4, 0);
    glVertex2f(4.5, -0.5);

  glEnd();

  glBegin(GL_QUADS);

    glColor3ub(192, 192, 192);
    //glNormal3f();
    glVertex2f(4, 0);
    glVertex2f(4.5, -0.5);
    glVertex2f(4.5, 4.5);
    glVertex2f(4, 4);

  glEnd();

  glBegin(GL_QUADS);

    glColor3ub(192, 192, 192);
    //glNormal3f();
    glVertex2f(4, 4);
    glVertex2f(4.5, 4.5);
    glVertex2f(-0.5, 4.5);
    glVertex2f(0, 4);

  glEnd();

  glBegin(GL_QUADS);

    glColor3ub(192, 192, 192);
    //glNormal3f();
    glVertex2f(0, 4);
    glVertex2f(-0.5, 4.5);
    glVertex2f(-0.5, -0.5);
    glVertex2f(0, 0);

  glEnd();
}

void drawGrid(){                            // Draws all the tiles for the game.
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 4; j++){
      drawTile(i, j, Tiles[i][j].textLeft, Tiles[i][j].textBottom);
    }
  }
}

void initGameBoard(){                         // Initializes the the tiles for the game
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 4; j++){
      Tiles[i][j].left = i;
      Tiles[i][j].bottom = j;
      Tiles[i][j].textLeft = i*0.25;
      Tiles[i][j].textBottom = j*0.25;
    }
  }
  Tiles[3][3].textLeft = -1;
  Tiles[3][3].textBottom = -1;
  whiteSpace[0] = 3;                // Initialize white space as the top right tile
  whiteSpace[1] = 3;
}

void swapPieces(int dirX, int dirY){          // Function that swaps the tiles after an arrow key is pressed.
  int x = whiteSpace[0];
  int y = whiteSpace[1];
  struct Tile temp = Tiles[x][y];
  if(dirY == 0){                              // Swap Tiles horizantally
    Tiles[x][y] = Tiles[(x+dirX+4)%4][y];
    Tiles[(x+dirX+4)%4][y] = temp;
    whiteSpace[0] = (whiteSpace[0] + dirX + 4)%4;
  }
  else if(dirX == 0){                         // Swap Tiles Vertically
    Tiles[x][y] = Tiles[x][(y+dirY+4)%4];
    Tiles[x][(y+dirY+4)%4] = temp;
    whiteSpace[1] = (whiteSpace[1]+dirY+4)%4;
  }
}

void randomize(){                               // Calls 100 swapPieces operations with random numbers in order to randomize the locations of everything
  int move;
  for(int i = 0; i < 100; i++){
    move = rand()%4;
    if(move == 0){
      swapPieces(1,0);
    }
    else if(move == 1){
      swapPieces(0,1);
    }
    else if(move == 2){
      swapPieces(-1,0);
    }
    else if(move == 3){
      swapPieces(0,-1);
    }
  }
}

void key(unsigned char ch,int x,int y)          // Extra Controls
{
  // Reset Everything
  if (ch == '0'){
    initGameBoard();
    moves = 0;
  }
  // Randomly move tiles
  else if (ch == 'r'){
    randomize();
    moves = 0;
  }
  // Change picture in game
  else if (ch == 'n'){
    textMode = 1 - textMode;
    moves = 0;
    initGameBoard();
  }
  // Exit animation
  else if (ch == 27){
    exit(0);
  }
  Project(0,asp,dim);
  //  Redisplay
  glutPostRedisplay();
}

void special(int key,int x,int y){							// What happens when things are pressed
  //  Swaps the white piece with the piece to the right
  if (key == GLUT_KEY_RIGHT){
    swapPieces(1,0); 
    moves++;
  }
  //  Swaps the white piece with the piece to the left
  else if (key == GLUT_KEY_LEFT){
    swapPieces(-1,0); 
    moves++;
  }
  //  Swaps the white piece with the piece above it
  else if (key == GLUT_KEY_UP){
    swapPieces(0,1); 
    moves++;
  }
  //  Swaps the white piece with the piece below it
  else if (key == GLUT_KEY_DOWN){
    swapPieces(0,-1); 
    moves++;
  }
    

  Project(0,asp,dim);
  //  Tell GLUT it is necessary to redisplay the scene
  glutPostRedisplay();
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);   //Clear Everything
  glEnable(GL_DEPTH_TEST);
  glLoadIdentity();

  glShadeModel(GL_FLAT);

  glPushMatrix();
  glTranslatef(-2.0, -2.0, 0);              // Draw Gameboard and the frame around it
  drawGrid();
  frame();
  glPopMatrix();

  glWindowPos2i(5,2);
  Print("Welcome! Moves so far: %d", moves);

  glFlush();
  glutSwapBuffers();    
}

void reshape(int width,int height) {							// This is called when the window is resized
  asp = (height>0) ? (double)width/height : 1;
  //  Set the viewport to the entire window
  glViewport(0,0, width,height);
  //  Set projection
  Project(0,asp,dim);	
}

int main(int argc,char* argv[]){								//Start GLUT and tell it what to do
  initGameBoard();
  //  Initialize GLUT and process user parameters
  glutInit(&argc,argv);
  //  Request double buffered, true color window 
  glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
  //  Request 750 x 750 pixel window
  glutInitWindowSize(750,750);
  //  Create the window
  glutCreateWindow("Sami Meharzi: Final Project");
  //  Tell GLUT to call "display" when the scene should be drawn
  glutDisplayFunc(display);
  //  Tell GLUT to call "reshape" when the window is resized
  glutReshapeFunc(reshape);
  //  Tell GLUT to call "special" when an arrow key is pressed
  glutSpecialFunc(special);
  //  Tell GLUT to call "key" when a key is pressed
  glutKeyboardFunc(key);
  //Load Textures
  texture[0] = LoadTexBMP("pictures/palace.bmp");
  texture[1] = LoadTexBMP("pictures/zoidberg.bmp");
  //  Pass control to GLUT so it can interact with the user
  ErrCheck("init");
  glutMainLoop();
  //  Return code
  return 0;
}