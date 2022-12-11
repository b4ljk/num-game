#include "DS.h"

#define CAR_NUMBER 3

//! deprecation aldaag arilgah
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

GLuint obj;
GLuint image;
int foot_y = 200;
int div_y = 220;
int end_y = 160;

int a = 0;
int hurd = 1;
int steerSpeed = 1;
int temp = 0;
int seconds = 0;
int distance = 178;
int tulsh = 178;

int game_state = 0;

void moveDivider();
void moveRoad();
void moveCar();
void periodicFunction(int);
void moveFuel();

// load audio using openal

int lane[CAR_NUMBER];
int pos[CAR_NUMBER];
int speeds[CAR_NUMBER];
int speedsTemp[CAR_NUMBER];

GLdouble width = 1480, height = 900;
bool carMoveLeft = false;
bool carMoveRight = false;
bool carMoveFast = false;
bool carStopped = false;
bool gameStopped = false;
bool horn = false;
bool startColor = false;
bool highlightExit = false;
bool reachedEnd = false;
bool gameCompleted = false;
bool isFuelOver = false;

// Car variables
int car_x_coordinate = 0;
int car_y_coordinate = -100;

int fuel_x = 0;
int fuel_y = -80;

void maindisp() {

  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  switch (game_state) {
  case 1:
    glClearColor(0.5, 0.5, 0.5, 0.0);
    drawFootPath();
    drawSurroundings();
    drawDivider();
    // drawEnd();
    drawCar();
    drawOther();
    drawTime();
    drawDistanceBar();
    drawFuelBar();
    drawFuel();
    break;

  case 0:
    drawMainMenu();

    break;

  case 2:
    glClearColor(0.5, 0.5, 0.5, 0.0);
    drawFootPath();
    drawSurroundings();
    drawDivider();
    if (gameCompleted)
      drawEnd();

    if (isFuelOver)
      fuelMessage();

    drawCar();
    drawOther();
    drawDistanceBar();
    drawFuelBar();
    drawExitMenu();
    drawTime();
    break;
  }

  glFlush();
  glutSwapBuffers();
}

GLuint loadBMP_custom(const char *imagepath) {
  unsigned char header[54];
  unsigned int dataPos;
  unsigned int width, height;
  unsigned int imageSize;
  unsigned char *l_texture;
  unsigned char *data;

  printf("filename: %s\n", imagepath);
  FILE *file = fopen(imagepath, "rb");
  if (!file) {
    printf("Image could not be opened\n");
    return 0;
  } else {
    printf("Image opened\n");
  }

  if (fread(header, 1, 54, file) != 54) {
    printf("Not correct\n");
    return false;
  }

  if (header[0] != 'B' || header[1] != 'M') {
    printf("Not correct\n");
    return 0;
  }
  dataPos = *(int *)&(header[0x0A]);
  imageSize = *(int *)&(header[0x22]);
  width = *(int *)&(header[0x12]);
  height = *(int *)&(header[0x16]);
  RGBTRIPLE rgb;
  int j = 0;
  l_texture = (byte *)malloc(width * height * 4);

  // And fill it with zeros
  memset(l_texture, 0, width * height * 4);
  // At this point we can read every pixel of the image
  for (int i = 0; i < width * height; i++) {
    // We load an RGB value from the file
    fread(&rgb, sizeof(rgb), 1, file);

    // And store it
    l_texture[j + 0] = rgb.rgbtRed;   // Red component
    l_texture[j + 1] = rgb.rgbtGreen; // Green component
    l_texture[j + 2] = rgb.rgbtBlue;  // Blue component
    l_texture[j + 3] = 255;           // Alpha value
    j += 4;                           // Go to the next position
  }

  data = new unsigned char[imageSize];

  fread(data, 1, imageSize, file);

  fclose(file);

  GLuint textureID;
  glGenTextures(1, &textureID);

  glBindTexture(GL_TEXTURE_2D, textureID);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR,
               GL_UNSIGNED_BYTE, data);

  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                  GL_REPEAT); // If the u,v coordinates overflow the range 0,1
                              // the image is repeated
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                  GL_LINEAR); // The magnification function ("linear" produces
                              // better results)
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_NEAREST); // The minifying function

  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

  glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
               l_texture);

  gluBuild2DMipmaps(GL_TEXTURE_2D, 4, width, height, GL_RGBA, GL_UNSIGNED_BYTE,
                    l_texture);

  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  return textureID;
}

void mouse_hover(int x, int y) {
  if (x >= 630 && x <= 810 && y >= 320 && y <= 405) {
    startColor = true;
    highlightExit = false;
  }

  else if (x >= 630 && x <= 810 && y >= 490 && y <= 575) {
    startColor = false;
    highlightExit = true;
  }

  else {
    highlightExit = false;
    startColor = false;
  }
}
void init() {
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-240.0, 240.0, -160.0, 160.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  std::cout << "pids";
  image = loadBMP_custom("/home/eggs/Documents/webs/Tests/Texture.bmp");
}
int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowSize((int)width, (int)height);
  glutCreateWindow("Uraldaan");
  // glutFullScreen();

  gluOrtho2D(-240.0, 240.0, -160.0, 160.0);
  init();
  glutDisplayFunc(maindisp);
  glutTimerFunc(100, periodicFunction, 0);

  glutSpecialFunc(keyBoardFunc);
  glutSpecialUpFunc(keyboard_up_func);
  glutKeyboardFunc(normalKeyBoardFunc);
  glutMouseFunc(mouse_func);
  glutPassiveMotionFunc(mouse_hover);

  glutMainLoop();
  return 0;
}

void drawCar(void) {
  glBindTexture(GL_TEXTURE_2D, image);
  glPushMatrix();

  glTranslated(car_x_coordinate, car_y_coordinate, 0.0);

  glColor3f(0.34, 1.0, 1.0);

  glRectd(2, 10, -2, -10);
  glRectf(-8, 12, 8, 13);
  glRectf(-10.0, 9.0, -8.0, 15.0);
  glRectf(8.0, 9.0, 10.0, 15.0);

  glBegin(GL_LINES);
  glVertex2f(8.0, 11.0);
  glVertex2f(6.0, 7.0);
  glVertex2f(6.0, 7.0);
  glVertex2f(6.0, -7.0);
  glVertex2f(6.0, -7.0);
  glVertex2f(10.0, -12.0);
  glVertex2f(-8.0, 11.0);
  glVertex2f(-6.0, 7.0);
  glVertex2f(-6.0, 7.0);
  glVertex2f(-6.0, -7.0);
  glVertex2f(-6.0, -7.0);
  glVertex2f(-10.0, -12.0);
  glVertex2f(10.0, -12.0);
  glVertex2f(-10.0, -12.0);
  glEnd();

  glRectf(-11.0, -16.0, -9.0, -8.0);
  glRectf(9.0, -16.0, 11.0, -8.0);
  glRectf(-7.0, -14.0, -5.0, -12.0);
  glRectf(5.0, -14.0, 7.0, -12.0);

  glBegin(GL_POINTS);
  glVertex2f(-7, -15);
  glVertex2f(-5, -15);
  glVertex2f(-8, -16);
  glVertex2f(-4, -16);
  glVertex2f(-6, -16);
  glVertex2f(-6, -17);
  glEnd();

  glPopMatrix();
}

void drawOtherCars(int i) {
  glPushMatrix();

  glTranslated((lane[i] - 1) * 37, pos[i], 0.0);

  switch (speeds[i]) {
  case 2:
    glColor3f(0.0, 1.0, 0.0);
    break;
  case 3:
    glColor3f(0.0, 0.0, 1.0);
    break;
  case 4:
  case 5:
  case 6:
  case 7:
    glColor3f(1.0, 0.0, 0.0);
    break;
  case 0:
    glColor3f(0.0, 0.0, 0.0);
    break;
  }

  glRectd(2, 10, -2, -10);
  glRectf(-8, 12, 8, 13);
  glRectf(-10.0, 9.0, -8.0, 15.0);
  glRectf(8.0, 9.0, 10.0, 15.0);

  glBegin(GL_LINES);
  glVertex2f(8.0, 11.0);
  glVertex2f(6.0, 7.0);
  glVertex2f(6.0, 7.0);
  glVertex2f(6.0, -7.0);
  glVertex2f(6.0, -7.0);
  glVertex2f(10.0, -12.0);
  glVertex2f(-8.0, 11.0);
  glVertex2f(-6.0, 7.0);
  glVertex2f(-6.0, 7.0);
  glVertex2f(-6.0, -7.0);
  glVertex2f(-6.0, -7.0);
  glVertex2f(-10.0, -12.0);
  glVertex2f(10.0, -12.0);
  glVertex2f(-10.0, -12.0);
  glEnd();

  glRectf(-11.0, -16.0, -9.0, -8.0);
  glRectf(9.0, -16.0, 11.0, -8.0);
  glRectf(-7.0, -14.0, -5.0, -12.0);
  glRectf(5.0, -14.0, 7.0, -12.0);

  glBegin(GL_POINTS);
  glVertex2f(-7, -15);
  glVertex2f(-5, -15);
  glVertex2f(-8, -16);
  glVertex2f(-4, -16);
  glVertex2f(-6, -16);
  glVertex2f(-6, -17);
  glEnd();

  glPopMatrix();
}

void drawFootPath() {
  int i, y;
  glPushMatrix();

  // Draw right side foot path
  glTranslated(60, 0, 0);
  y = foot_y + 20;

  for (i = 0; i < 20; i++) {
    if (a == 0) {
      if (i % 2 == 0)
        glColor3f(1.0, 1.0, 1.0);
      else
        glColor3f(1.0, 1.0, 0.0);
    }

    else {
      if (i % 2 == 1)
        glColor3f(1.0, 1.0, 1.0);
      else
        glColor3f(1.0, 1.0, 0.0);
    }

    y -= 20;
    glRectd(5, y, -5, y - 20);
  }
  glPopMatrix();

  // Draw left side foot path
  glPushMatrix();
  glTranslated(-60, 0, 0);

  y = foot_y + 20;
  for (i = 0; i < 20; i++) {

    if (a == 0) {
      if (i % 2 == 0)
        glColor3f(1.0, 1.0, 1.0);
      else
        glColor3f(1.0, 1.0, 0.0);
    }

    else {
      if (i % 2 == 1)
        glColor3f(1.0, 1.0, 1.0);
      else
        glColor3f(1.0, 1.0, 0.0);
    }

    y -= 20;
    glRectd(5, y, -5, y - 20);
  }
  glPopMatrix();
}

void drawDivider() {
  int i;
  int y = div_y + 80;
  glColor3f(1.0, 1.0, 1.0);

  for (i = 0; i < 8; i++) {
    y -= 80;
    glRectd(22, y, 18, y - 40);
    glRectd(-18, y, -22, y - 40);
  }
}

void drawSurroundings() {
  glBindTexture(GL_TEXTURE_2D, image);
  glColor3f(0.0, 1.0, 0.0);
  glRectd(240, 160, 65, -160);
  glRectd(-240, 160, -65, -160);
}

void stopGame() {
  hurd = 0;
  steerSpeed = 0;
}

void resumeGame() {
  hurd = 2;
  steerSpeed = 1;
}

void drawOther() {
  int i;
  for (i = 0; i < CAR_NUMBER; i++) {
    drawOtherCars(i);
  }
}

void setCars() {
  int i;
  for (i = 0; i < CAR_NUMBER; i++) {
    lane[i] = i;
    pos[i] = 110 + rand() % 100;
    speeds[i] = 1 + i + rand() % 4;
  }
}

void moveDivider() {
  div_y -= hurd;
  if (div_y < 120 && distance > 0) {
    div_y = 200;

    if (carMoveFast) {
      distance -= 1.5;
      tulsh -= 4;
    } else {

      distance -= 0.5;
      tulsh -= 2;
    }

    if (tulsh < 0)
      isFuelOver = true;

    if (distance < 5)
      reachedEnd = true;
  }
}

void moveCar() {
  if (carMoveLeft)
    car_x_coordinate -= steerSpeed;

  else if (carMoveRight)
    car_x_coordinate += steerSpeed;

  if (car_x_coordinate > 45 || car_x_coordinate < -45) {
    game_state = 2;
    gameStopped = true;
  }
}

void moveRoad() {
  foot_y -= hurd;
  if (foot_y < 160) {
    foot_y = 180;
    if (a == 0)
      a = 1;
    else
      a = 0;
  }
}

void periodicFunction(int v) {
  if (gameStopped)
    stopGame();

  else
    resumeGame();

  if (hurd != 0) {
    if (carMoveFast)
      hurd = 6;

    else
      hurd = 2;
  }

  if (isFuelOver) {
    gameStopped = true;
    game_state = 2;
  }

  moveRoad();
  moveDivider();
  moveCar();
  moveOtherCars();
  moveEnd();
  moveFuel();

  if (!detectCollision() && !gameStopped && game_state == 1)
    temp += 15;

  if (temp > 1000) {
    temp = 0;
    seconds++;
  }

  glutPostRedisplay();
  glutTimerFunc(10, periodicFunction, v);
}

void moveOtherCars() {
  int i;
  for (i = 0; i < CAR_NUMBER; i++) {
    pos[i] += -hurd + speeds[i];

    if (pos[i] < -200 || pos[i] > 200) {
      pos[i] = 200 + rand() % 100;
      speeds[i] = 2 + rand() % 4;
    }
  }

  if (horn) {
    speeds[(car_x_coordinate + 60) / 40]++;
    if (speeds[(car_x_coordinate + 60) / 40] > 7)
      speeds[(car_x_coordinate + 60) / 40] = 7;
    horn = false;
  }
}

int detectCollision() {
  if (game_state != 1)
    return 0;

  int i, limit;
  for (i = 0; i < CAR_NUMBER; i++) {
    if (pos[i] < -70 && pos[i] > -130) {
      limit = (i - 1) * 40;
      if (car_x_coordinate < limit + 22 && car_x_coordinate > limit - 22) {
        speeds[i] = 0;
        gameStopped = true;
        game_state = 2;
        return 1;
      }
    }
  }

  if ((fuel_x > car_x_coordinate && fuel_x - car_x_coordinate < 20) ||
      (fuel_x < car_x_coordinate && car_x_coordinate - fuel_x < 20)) {
    if (fuel_y < -80 && fuel_y > -120) {
      tulsh += 40;
      if (tulsh > 178)
        tulsh = 178;
      fuel_y = 600 + rand() % 150;
      fuel_x = (rand() % 3 - 1) * 37;
    }
  }

  return 0;
}

void drawScore(int score) {
  int temp = score;
  int str[20], i = 0;

  while (temp > 0) {
    str[i++] = (temp % 10);
    temp /= 10;
  }
  i--;
  while (i >= 0) {
    glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i--] + '0');
  }
  if (score == 0)
    glutStrokeCharacter(GLUT_STROKE_ROMAN, '0');
}

void drawDistanceBar() {
  glPushMatrix();
  glColor3f(0.0, 0.0, 0.0);

  glTranslated(-75, 40, 0);
  glBegin(GL_LINE_LOOP);
  glVertex2f(5, 90);
  glVertex2f(5, -90);
  glVertex2f(-5, -90);
  glVertex2d(-5, 90);
  glEnd();
  glPopMatrix();

  glPushMatrix();
  glTranslated(-75, -49, 0);
  glColor3f(0.6, 0.6, 0.6);
  glRectd(4, 0, -4, distance);
  glPopMatrix();
}

void drawFuelBar() {
  glPushMatrix();
  glColor3f(0.0, 0.0, 0.0);

  glTranslated(75, 40, 0);
  glBegin(GL_LINE_LOOP);
  glVertex2f(5, 90);
  glVertex2f(5, -90);
  glVertex2f(-5, -90);
  glVertex2d(-5, 90);
  glEnd();
  glPopMatrix();

  glPushMatrix();
  glTranslated(75, -49, 0);
  glColor3f(0.6, 0.6, 0.6);
  glRectd(4, 0, -4, tulsh);
  glPopMatrix();
}

void drawEnd() {
  int i, j;
  for (i = 0; i < 5; i++) {
    if (i % 2 == 0)
      glColor3f(0.0, 0.0, 0.0);
    else
      glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();

    glTranslated(-55, end_y + 10 * i, 0);

    for (j = 0; j < 11; j++) {
      if (i % 2) {
        if (j % 2 == 0)
          glColor3f(0.0, 0.0, 0.0);
        else
          glColor3f(1.0, 1.0, 1.0);

      }

      else {
        if (j % 2)
          glColor3f(0.0, 0.0, 0.0);
        else
          glColor3f(1.0, 1.0, 1.0);
      }

      glRectd(10 * j, 0, 10 * (j + 1), 10);
    }

    glPopMatrix();
  }
}

void moveEnd() {
  if (reachedEnd)
    end_y -= hurd;

  if (end_y < -125) {
    gameStopped = true;
    gameCompleted = true;
    game_state = 2;
  }
}

void drawFuel() {
  glPushMatrix();
  glTranslated(fuel_x, fuel_y, 0);
  glColor3f(0.0, 1.0, 0.0);
  glRectf(5, 5, -5, -5);
  glPopMatrix();

  glPushMatrix();
  glTranslated(fuel_x, fuel_y + 5, 0);
  glBegin(GL_LINE_LOOP);
  glVertex2f(5, 0);
  glVertex2f(5, 5);
  glVertex2f(-3, 5);
  glVertex2d(-5, 0);
  glEnd();
  glPopMatrix();
}

void moveFuel() {
  fuel_y -= hurd;

  if (fuel_y < -200) {
    fuel_y = 600 + rand() % 150;
    fuel_x = (rand() % 3 - 1) * 37;
  }
}
