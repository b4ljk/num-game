#include "DS.h"

void draw_string(std::string str) {
  for (unsigned int i = 0; i < str.length(); i++) {
    glutStrokeCharacter(GLUT_STROKE_ROMAN, *(str.begin() + i));
  }
}

void drawMainMenu() {
  glClearColor(0.5, 0.5, 0.5, 0.0);
  glColor3f(0.0, 0.0, 0.0);
  drawFootPath();
  drawSurroundings();
  drawDivider();
  drawCar();

  glColor3f(1.0, 1.0, 1.0);
  glPushMatrix();
  glTranslated(0, 30, 0);
  glBegin(GL_LINE_LOOP);
  glVertex2f(30, 15);
  glVertex2f(30, -15);
  glVertex2f(-30, -15);
  glVertex2d(-30, 15);
  glEnd();
  glPopMatrix();

  glPushMatrix();
  glTranslated(-20, 30, 0);
  glScalef(0.1, 0.1, 0.1);
  glColor3f(1.0, 1.0, 1.0);
  draw_string("EHLEH");

  glPopMatrix();

  glColor3f(1.0, 1.0, 1.0);

  glPushMatrix();
  glTranslated(0, -30, 0);
  glBegin(GL_LINE_LOOP);
  glVertex2f(30, 15);
  glVertex2f(30, -15);
  glVertex2f(-30, -15);
  glVertex2d(-30, 15);
  glEnd();
  glPopMatrix();

  glPushMatrix();
  glTranslated(-15, -30, 0);
  glScalef(0.1, 0.1, 0.1);
  draw_string("XAAX");

  glPopMatrix();

  if (startColor) {
    glColor3f(1.0, 0.0, 0.0);

    glPushMatrix();
    glTranslated(0, 30, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(35, 20);
    glVertex2f(35, -20);
    glVertex2f(-35, -20);
    glVertex2d(-35, 20);
    glEnd();
    glPopMatrix();
  }

  if (highlightExit) {
    glColor3f(1.0, 0.0, 0.0);

    glPushMatrix();
    glTranslated(0, -30, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(35, 20);
    glVertex2f(35, -20);
    glVertex2f(-35, -20);
    glVertex2d(-35, 20);
    glEnd();
    glPopMatrix();
  }
}

void drawExitMenu() {
  glColor3f(1.0, 1.0, 1.0);
  glPushMatrix();
  glTranslated(0, 30, 0);
  glBegin(GL_LINE_LOOP);
  glVertex2f(30, 15);
  glVertex2f(30, -15);
  glVertex2f(-30, -15);
  glVertex2d(-30, 15);
  glEnd();
  glPopMatrix();

  glPushMatrix();
  glTranslated(-25, 30, 0);
  glScalef(0.1, 0.1, 0.1);
  glColor3f(1.0, 1.0, 1.0);
  draw_string("RESTART");

  glPopMatrix();

  glColor3f(1.0, 1.0, 1.0);

  glPushMatrix();
  glTranslated(0, -30, 0);
  glBegin(GL_LINE_LOOP);
  glVertex2f(30, 15);
  glVertex2f(30, -15);
  glVertex2f(-30, -15);
  glVertex2d(-30, 15);
  glEnd();
  glPopMatrix();

  glPushMatrix();
  glTranslated(-15, -30, 0);
  glScalef(0.1, 0.1, 0.1);
  draw_string("EXIT");

  glPopMatrix();

  if (startColor) {
    glColor3f(1.0, 0.0, 0.0);

    glPushMatrix();
    glTranslated(0, 30, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(35, 20);
    glVertex2f(35, -20);
    glVertex2f(-35, -20);
    glVertex2d(-35, 20);
    glEnd();
    glPopMatrix();
  }

  if (highlightExit) {
    glColor3f(1.0, 0.0, 0.0);

    glPushMatrix();
    glTranslated(0, -30, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(35, 20);
    glVertex2f(35, -20);
    glVertex2f(-35, -20);
    glVertex2d(-35, 20);
    glEnd();
    glPopMatrix();
  }
}

void drawTime() {
  glColor3f(1.0, 1.0, 1.0);
  glPushMatrix();
  glTranslated(-200, 90, 0);
  glBegin(GL_LINE_LOOP);
  glVertex2f(50, 15);
  glVertex2f(50, -15);
  glVertex2f(-30, -15);
  glVertex2d(-30, 15);
  glEnd();
  glPopMatrix();

  glPushMatrix();
  glTranslated(-220, 85, 0);
  glScalef(0.1, 0.1, 0.1);
  glColor3f(1.0, 1.0, 1.0);
  draw_string("Time: ");
  glPopMatrix();

  glPushMatrix();
  glTranslated(-180, 85, 0);
  glScalef(0.1, 0.1, 0.1);
  glColor3f(1.0, 0.0, 0.0);
  drawScore(seconds);
  glPopMatrix();
}

void fuelMessage() {
  glPushMatrix();
  glTranslated(75, -70, 0);
  glScalef(0.1, 0.1, 0.1);
  glColor3f(1.0, 0, 0);
  draw_string("Fuel Exhausted\n");
  glPopMatrix();
}
void keyBoardFunc(int key, int x, int y) {
  switch (key) {
  case GLUT_KEY_LEFT:
    carMoveLeft = true;
    carMoveRight = false;
    break;
  case GLUT_KEY_RIGHT:
    carMoveRight = true;
    carMoveLeft = false;
    break;
  case GLUT_KEY_UP:
    carMoveFast = true;
    break;
  }
}

void keyboard_up_func(int k, int x, int y) {
  switch (k) {
  case GLUT_KEY_LEFT:
    carMoveLeft = false;
    break;
  case GLUT_KEY_RIGHT:
    carMoveRight = false;
    break;

  case GLUT_KEY_UP:
    carMoveFast = false;
    break;
  case GLUT_KEY_DOWN:
    carStopped = false;
    break;
  }
}

void normalKeyBoardFunc(unsigned char key, int x, int y) {
  if (game_state == 1) {
    switch (key) {
    case 'H':
    case 'h':
      horn = true;
      break;
    }
  }

  else if (game_state == 0) {
    if (key == 13) {
      setCars();
      game_state = 1;
    }
  }
}

void mouse_func(int button, int state, int x, int y) {
  switch (game_state) {
  case 0:
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
      if (x >= 630 && x <= 810 && y >= 320 && y <= 405) {
        setCars();
        game_state = 1;
      }

      else if (x >= 630 && x <= 810 && y >= 490 && y <= 575)
        exit(0);
    }
    break;

  case 2:
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
      if (x >= 630 && x <= 810 && y >= 320 && y <= 405) {
        gameStopped = false;
        gameCompleted = false;
        reachedEnd = false;
        seconds = 0;
        distance = 178;
        tulsh = 178;
        isFuelOver = false;
        end_y = 160;
        setCars();
        game_state = 1;
        car_x_coordinate = 0;
      }

      else if (x >= 630 && x <= 810 && y >= 490 && y <= 575)
        exit(0);
    }
    break;
  }
}