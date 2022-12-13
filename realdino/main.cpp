#include "draw.h"
#include <GL/freeglut_std.h>
#include <GL/gl.h>
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
int score = 0;
int wingX = 0;
int wingY = 0;

class cloud {
  float location;
  float scale;

public:
  cloud() {
    this->location = 4000;
    this->scale = 1;
  }
  cloud(float _location) { this->location = _location; }
  void changeLoc(float globalSpeed) { this->location -= globalSpeed; }
  float getLoc() { return this->location; }
  ~cloud() {}
};

vector<cloud> clouds;
class tree {
  float location;
  float scale;

public:
  tree() {
    this->location = 4000;
    this->scale = 1;
  }
  tree(float _location, float _scale) {
    this->location = _location;
    this->scale = _scale;
  }
  void changeLoc(float globalSpeed) { this->location -= globalSpeed; }
  float getLoc() { return this->location; }
  ~tree() {}
};
vector<tree> trees;

class bat {
  float location;

public:
  bat() { this->location = 4000; }
  bat(float _location) { this->location = _location; }
  void changeLoc(float globalSpeed) { this->location -= globalSpeed; }
  float getLoc() { return this->location; }
  ~bat() {}
};
vector<bat> bats;

bool collision(double len, float _location) {
  if (abs(130 + 80 - (_location + 80 + 50)) <= 100 + 80) {
    if (5 * 3 + w <= 550 * len)
      return 1;
    return 0;
  }
  return 0;
}
bool batCollision(double len, float _location) {
  if (abs(130 + 80 - (_location + 80 + 50)) <= 40 + 80) {
    if ((5 * 3 + w <= 550 * len && !isDucking))
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
  if (key == GLUT_KEY_F4 && isGameOver) {
    isGameOver = false;
    score = 0;
    globalSpeed = 10;
    w = 200;
    x_ = 2500;
    trees.clear();
    clouds.clear();
    bats.clear();
  }
}
void specialKeyOnRelease(int key, int x, int y) {
  if (key == GLUT_KEY_DOWN) {
    isDucking = false;
  }
}

void draw_string(std::string str) {
  glPushMatrix();
  if (isGameOver) {
    glTranslated(1500, 2000, 0);
    for (unsigned int i = 0; i < str.length(); i++) {
      glutStrokeCharacter(GLUT_STROKE_ROMAN, *(str.begin() + i));
    }
    str = "Press F4 to Play Again";
    glTranslated(-1250, -200, 0);
    for (unsigned int i = 0; i < str.length(); i++) {
      glutStrokeCharacter(GLUT_STROKE_ROMAN, *(str.begin() + i));
    }
    glPopMatrix();
  } else {
    glTranslated(3000, 3800, 0);

    for (unsigned int i = 0; i < str.length(); i++) {
      glutStrokeCharacter(GLUT_STROKE_ROMAN, *(str.begin() + i));
    }
    glPopMatrix();
  }
}

void draw_circle(double theta, double inner_radius, double outer_radius, int x,
                 int y, int sin_sign = 1, int cos_sign = 1, float r = 0.0,
                 float g = 0.0, float b = 0.0) {
  glBegin(GL_POINTS);
  glColor3f(r / 255.0, g / 255.0, b / 255.0);
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
  } else {
    glutTimerFunc(1000, idleDisplay, 0);
  }
}

void drawBat(int x_, int y_) {
  glColor3f((0) / 255.0, (0) / 255.0, (0) / 255.0);
  glBegin(GL_TRIANGLE_STRIP);
  glVertex2f(x_, y_);
  glVertex2f(x_ + 100, y_ + 80);
  glVertex2f(x_ + 100, y_ - 30);
  glEnd();
  glBegin(GL_QUAD_STRIP);
  glVertex2f(x_ + 80, y_ - 20);
  glVertex2f(x_ + 220 - wingX, y_ - 15 - wingY);
  glVertex2f(x_ + 225, y_ - 100);
  glVertex2f(x_ + 170, y_ - 120);
  glEnd();
}

void drawCloud(int x_, int y_) {
  draw_circle(360, 0, 200, x_, 2000, 1, 1, 200, 200, 200);
  draw_circle(360, 0, 200, x_ + 150, 2000 + 200, 1, 1, 200, 200, 200);
  draw_circle(360, 0, 200, x_ - 115, 2000, 1, 1, 200, 200, 200);
}

void render(void) {
  glClear(GL_COLOR_BUFFER_BIT);

  glPointSize(2);
  glBegin(GL_POINTS);
  glColor3f((128) / 255.0, (128) / 255.0, (128) / 255.0);

  glEnd();

  if (!isGameOver) {
    draw_string("Score: " + to_string(score));
  } else {
    draw_string("Game Over");
  }

  glPointSize(2);
  glBegin(GL_POINTS);
  glColor3f((0) / 255.0, (0) / 255.0, (0) / 255.0);
  for (int i = 0; i < 100; i++) {
    glVertex2f(rand() % 4000, 200);
    glVertex2f((rand() + 31) % 4000, 150);
  }
  glEnd();
  globalSpeed += 0.1;
  score += 1;
  if (score % 6 == 0) {
    if (w <= 200) {
      if (walk == -20)
        walk = 20;
      else {
        walk = -20;
      }
    } else {
      walk = 0;
    }
    if (wingX == 140) {
      wingX = 0;
      wingY = 0;
    } else {
      wingX = 140;
      wingY = 190;
    }
  }

  if (rand() % 100 == 0) {
    trees.push_back(tree(4000 + rand() % 400, (rand() % 50) / 100.0 + 0.5));
  }
  if (rand() % 100 == 0) {
    bats.push_back(bat(4000 + rand() % 400));
  }

  if (rand() % 100 == 0) {
    clouds.push_back(cloud(4000 + rand() % 400));
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
  for (int i = 0; i < bats.size(); i++) {
    drawBat(bats[i].getLoc(), 630);
    bats[i].changeLoc(globalSpeed);
    if (batCollision(0.9, bats[i].getLoc())) {
      isGameOver = true;
    }
    if (bats[i].getLoc() < 0) {
      bats.erase(bats.begin() + i);
    }
  }
  for (int i = 0; i < clouds.size(); i++) {
    drawCloud(clouds[i].getLoc(), 0);
    clouds[i].changeLoc(globalSpeed);
    if (clouds[i].getLoc() < 0) {
      clouds.erase(clouds.begin() + i);
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

  if (isJumping == 1) {
    if (w <= 1300) {
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
