#include <ostream>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef __WIN64
#include <GL/glut.h>
#include <windows.h> //for Sleep() only
#elif __WIN32
#include <GL/glut.h>
#include <windows.h> //for Sleep() only
#elif __APPLE_CC__
#include <GLUT/glut.h>
#elif __linux
#include <GL/glew.h>
#include <GL/glut.h>
#elif __unix
#include <GL/glut.h>
#endif
// #include <AL/al.h>
// #include <AL/alc.h>
#include <iostream>
#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <vector>

#define far
#define near
#define FAR far
#define NEAR near

typedef unsigned char BYTE;
typedef unsigned char byte;
// TODO: zuuuj avah
// TODO: zuuuj avah
// TODO: zuuuj avah

typedef struct tagRGBTRIPLE {
  BYTE rgbtBlue;
  BYTE rgbtGreen;
  BYTE rgbtRed;
} RGBTRIPLE, *PRGBTRIPLE, NEAR *NPRGBTRIPLE, FAR *LPRGBTRIPLE;

typedef struct vertex {
  GLfloat x;
  GLfloat y;
  GLfloat z;
} Vertex;

typedef struct normal {
  GLfloat x;
  GLfloat y;
  GLfloat z;
} Normal;

typedef struct texture {
  GLfloat x;
  GLfloat y;
} Texture;

typedef struct face {
  GLint v1, v2, v3, v4;
  GLint n1, n2, n3, n4;
  GLint t1, t2, t3, t4;
} Face;

void drawCar();
void drawFootPath();
void drawDivider();
void drawSurroundings();
void stopGame();
void drawOtherCars(int);
void drawOther();
void setCars();
void moveOtherCars();
int detectCollision();
void drawString(std::string);
void drawMainMenu();
void drawExitMenu();
void drawTime();
void stopGame();
void resumeGame();
void drawScore(int);
void drawDistanceBar();
void drawEnd();
void moveEnd();
void drawFuelBar();
void fuelMessage();
void drawFuel();
void keyBoardFunc(int key, int x, int y);
void mouse_func(int button, int state, int x, int y);
void normalKeyBoardFunc(unsigned char key, int x, int y);
void keyboard_up_func(int k, int x, int y);
extern bool carMoveLeft, carMoveRight, carMoveFast, carStopped, gameStopped,
    horn;
extern bool startColor, highlightExit;
extern bool reachedEnd, gameCompleted, isFuelOver;
extern int seconds;

extern int car_x_coordinate;
extern int car_y_coordinate;
extern int fuel_x;
extern int fuel_y;
extern int game_state;
extern int foot_y;
extern int div_y;
extern int end_y;
extern int distance;
extern int seconds;
extern int tulsh;