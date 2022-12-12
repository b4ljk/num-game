#include "draw.h"
#include <GL/freeglut_std.h>
#include <vector>
using namespace std;
int FpsCount = 30;
static double w = 200;
static int isJumping = 0;
static int walk = 0;
static int x_ = 2500;
bool isGameOver = false;
bool isDucking = false;
void keyInput(unsigned char key, int x, int y) {}
const double radian = 3.1415926535897932384 / 180;
float globalSpeed = 10;
class tree {
  float location;

public:
  tree() { this->location = 4000; }
  tree(float _location) { this->location = _location; }
  void changeLoc(float globalSpeed) { this->location -= globalSpeed; }
  float getLoc() { return this->location; }
  ~tree() {}
};
vector<tree> trees;

bool collision(double len, float _location) {
  if (abs(130 + 80 - (_location + 80 + 50)) <= 100 + 80) {
    if (5 * 3 + w <= 550 * len)
      return 1;
    return 0;
  }
  return 0;
}

void specialKeyInput(int key, int x, int y) {
  if (key == GLUT_KEY_UP && isJumping == 0 && w <= 200.0) {
    isJumping = 1;
  } else if (key == GLUT_KEY_DOWN) {
    isDucking = true;
  }
  //   glutPostRedisplay();
}
void specialKeyOnRelease(int key, int x, int y) {
  if (key == GLUT_KEY_DOWN) {
    isDucking = false;
  }
}

void draw_circle(double theta, double inner_radius, double outer_radius, int x,
                 int y, int sin_sign = 1, int cos_sign = 1) {
  glBegin(GL_POINTS);
  glColor3f(0.0 / 255.0, 0.0 / 255.0, 0.0 / 255.0);
  for (double r = outer_radius; r >= inner_radius; r -= 3.0) {
    for (double i = 0; i < theta; i++) {
      double degInRad = i * radian;
      glVertex2f(cos_sign * cos(degInRad) * r + x,
                 sin_sign * sin(degInRad) * r + y);
    }
  }
  glEnd();
}
void generate_tree(int x_, double len) {
  int x = 30;
  glColor3f((0) / 255.0, (0) / 255.0, (0) / 255.0);
  glBegin(GL_POLYGON);
  glVertex2f(x_, 250 * len);
  glVertex2f(x_ + x, 250 * len);
  glVertex2f(x_ + x, 650 * len);
  glVertex2f(x_, 650 * len);
  glEnd();

  draw_circle(180.0, 0.0, x / 2, x_ + x / 2, 650 * len);

  glBegin(GL_POLYGON);
  glVertex2f(x_ + x + 25, 400 * len);
  glVertex2f(x_ + x + 50, 400 * len);
  glVertex2f(x_ + x + 50, 600 * len);
  glVertex2f(x_ + x + 25, 600 * len);
  glEnd();

  draw_circle(180.0, 0.0, 25.0 / 2, x_ + x + 75.0 / 2, 600 * len);

  glBegin(GL_POLYGON);
  glVertex2f(x_ - 25, 400 * len);
  glVertex2f(x_ - 50, 400 * len);
  glVertex2f(x_ - 50, 600 * len);
  glVertex2f(x_ - 25, 600 * len);
  glEnd();

  draw_circle(180.0, 0.0, 25.0 / 2, x_ - 75.0 / 2, 600 * len);
  draw_circle(90.0, 25, 50, x_ + x, 400 * len, -1);
  draw_circle(90.0, 25, 50, x_, 400 * len, -1, -1);
}

void idleDisplay(int s) {
  glutPostRedisplay();
  if (!isGameOver) {
    glutTimerFunc(1000 / FpsCount, idleDisplay, 0);
  }
}

void render(void) {
  glClear(GL_COLOR_BUFFER_BIT);

  glPointSize(2);
  glBegin(GL_POINTS);
  glColor3f((0) / 255.0, (0) / 255.0, (0) / 255.0);
  for (int i = 0; i < 100; i++) {
    glVertex2f(rand() % 4000, 200);
    glVertex2f((rand() + 31) % 4000, 150);
  }
  glEnd();
  globalSpeed += 0.1;

  // generate tree with 1% chance
  if (rand() % 100 == 0) {
    trees.push_back(tree(4000 + rand() % 400));
  }
  for (int i = 0; i < trees.size(); i++) {
    generate_tree(trees[i].getLoc(), 0.9);
    trees[i].changeLoc(globalSpeed);
    if (collision(0.9, trees[i].getLoc())) {
      isGameOver = true;
    }
    if (trees[i].getLoc() < 0) {
      trees.erase(trees.begin() + i);
    }
  }
  glLineWidth(2);
  glBegin(GL_LINES);
  glColor3f((0) / 255.0, (0) / 255.0, (0) / 255.0);
  glVertex2f(0, 250);
  glVertex2f(4000, 250);
  glEnd();

  glLineWidth(10);
  drawDino(w, walk, isDucking);
  android1();

  if (w <= 200) {
    if (walk == -20)
      walk = 20;
    else {
      walk = -20;
    }
  } else {
    walk = 0;
  }

  if (isJumping == 1) {
    if (w <= 1000) {
      w = w + 99;
    } else {
      isJumping = 0;
    }
  } else if (w >= 200) {
    if (isDucking) {
      w = w - 150;
    } else {
      w = w - 99;
    }
  }
  glFlush();
}

void init(void) {
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glMatrixMode(GL_PROJECTION);
  gluOrtho2D(0.0, 4000, 0.0, 4000);
}

int main(int argc, char **argv) {
  srand(time(NULL));
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
  glutInitWindowSize(1230, 650);
  glutInitWindowPosition(50, 0);
  glutCreateWindow("Dinosaur!!");
  init();

  glutDisplayFunc(render);
  glutTimerFunc(50, idleDisplay, 5);

  glutKeyboardFunc(keyInput);
  glutSpecialFunc(specialKeyInput);
  glutSpecialUpFunc(specialKeyOnRelease);
  glutMainLoop();
}
