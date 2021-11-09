#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

GLfloat angle, fAspect, left, rigth, lookAtAngle;
GLint perspectiva;

void quadrilatero(float verts[4][3], int primitiva, float espessura)
{
  glLineWidth(espessura);
  glBegin(primitiva);
  for (int i = 0; i < 4; i++)
  {
    glVertex3fv(verts[i]);
  }
  glEnd();
}

void poligono(float verts[8][3], int primitiva, float espessura)
{
  glLineWidth(espessura);
  glBegin(primitiva);
  for (int i = 0; i < 8; i++)
  {
    glVertex3fv(verts[i]);
  }
  glEnd();
}

void triangulo(float verts[3][3], int primitiva, float espessura)
{
  glLineWidth(espessura);
  glBegin(primitiva);
  for (int i = 0; i < 3; i++)
  {
    glVertex3fv(verts[i]);
  }
  glEnd();
}

void linha(float x1, float y1, float z1, float x2, float y2, float z2, float espessura)
{
  glLineWidth(espessura);
  glBegin(GL_LINES);
  glVertex3f(x1, y1, z1);
  glVertex3f(x2, y2, z2);
  glEnd();
}

void Transposta(float matriz[4][4])
{
  float aux;
  for (int i = 0; i < 4; i++)
  {
    for (int j = i; j >= 0; j--)
    {
      aux = matriz[i][j];
      matriz[i][j] = matriz[j][i];
      matriz[j][i] = aux;
    }
  }
}

// função rotação no eixo x
void RotateX(float ang)
{
  float matriz[4][4] = {{1, 0, 0, 0},
                        {0, 1, 0, 0},
                        {0, 0, 1, 0},
                        {0, 0, 0, 1}};
  matriz[1][1] = cos(ang * M_PI / 180);
  matriz[1][2] = -sin(ang * M_PI / 180);
  matriz[2][1] = sin(ang * M_PI / 180);
  matriz[2][2] = cos(ang * M_PI / 180);
  Transposta(matriz);
  glMultMatrixf((float *)matriz);
}

// função rotação no eixo y
void RotateY(float ang)
{
  float matriz[4][4] = {{1, 0, 0, 0},
                        {0, 1, 0, 0},
                        {0, 0, 1, 0},
                        {0, 0, 0, 1}};
  matriz[0][0] = cos(ang * M_PI / 180);
  matriz[0][2] = sin(ang * M_PI / 180);
  matriz[2][0] = -sin(ang * M_PI / 180);
  matriz[2][2] = cos(ang * M_PI / 180);
  Transposta(matriz);
  glMultMatrixf((float *)matriz);
}

// função rotação no eixo z
void RotateZ(float ang)
{
  float matriz[4][4] = {{1, 0, 0, 0},
                        {0, 1, 0, 0},
                        {0, 0, 1, 0},
                        {0, 0, 0, 1}};

  matriz[0][0] = cos(ang * M_PI / 180.0);
  matriz[0][1] = -sin(ang * M_PI / 180.0);
  matriz[1][0] = sin(ang * M_PI / 180.0);
  matriz[1][1] = cos(ang * M_PI / 180.0);
  Transposta(matriz);
  glMultMatrixf((float *)matriz);
}

//função translação
void Translate(float dx, float dy, float dz)
{
  float matriz[4][4] = {{1, 0, 0, 0},
                        {0, 1, 0, 0},
                        {0, 0, 1, 0},
                        {0, 0, 0, 1}};
  matriz[0][3] = dx;
  matriz[1][3] = dy;
  matriz[2][3] = dz;
  Transposta(matriz);
  glMultMatrixf((float *)matriz);
}

// função escala
void Scale(float sx, float sy, float sz)
{
  float matriz[4][4] = {{1, 0, 0, 0},
                        {0, 1, 0, 0},
                        {0, 0, 1, 0},
                        {0, 0, 0, 1}};
  matriz[0][0] = sx;
  matriz[1][1] = sy;
  matriz[1][1] = sz;
  Transposta(matriz);
  glMultMatrixf((float *)matriz);
}

void display(void)
{
  float vertice1[3][3] = {{2, 3, 0}, {3, 2, 0}, {4, 3, 0}};
  float vertice2[3][3] = {{2, 3, 0}, {3, 2, 0}, {4, 3, 0}};
  float vertice3[4][3] = {{2, 3, 0}, {3, 2, 0}, {4, 3, 0}, {3, 1, 0}};
  float vertice4[3][3] = {{2, 3, 0}, {3, 2, 0}, {4, 3, 0}};
  float vertice5[4][3] = {{2, 3, 0}, {3, 2, 0}, {4, 3, 0}, {3, 1, 0}};
  float vertices[8][3] = {{3, 1, 0}, {3, 2, 0}, {3, 3, 0}, {2, 3, 0}, {2, 2, 0}, {1, 2, 0}, {1, 1, 0}, {2, 1, 0}};
  float vertices2[8][3] = {{3, 1, 0}, {3, 2, 0}, {3, 3, 0}, {2, 3, 0}, {2, 2, 0}, {1, 2, 0}, {1, 1, 0}, {2, 1, 0}};
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  glColor3f(0.0, 0.0, 1.0);
  Translate(-3, 0, 0);
  triangulo(vertice1, GL_TRIANGLES, 4);
  Translate(3, 2, 0);
  RotateZ(-180);
  Translate(-3, -2, 0);
  glColor3f(0.0, 0.0, 1.0);
  triangulo(vertice2, GL_TRIANGLES, 4);
  glColor3f(0.0, 0.0, 1.0);
  Translate(4, 4, 0);   //Move para 3 quadrante para rotacionar
  RotateZ(90);          // Rotaciona em z
  Translate(-5, -3, 0); // Move para a posicao correta
  glColor3f(0.0, 0.0, 1.0);
  Translate(4, -4, 0);
  RotateZ(90);
  Translate(4, -4, 0);
  RotateZ(90);
  Translate(2, -8, 0);
  RotateZ(-45);
  Scale(0.70, 0.70, 0.70);
  Translate(-1.97, 4, 0);
  poligono(vertices, GL_TRIANGLE_FAN, 2);
  RotateZ(180);
  Translate(-1.91, -6.12, 0);
  poligono(vertices2, GL_TRIANGLE_FAN, 2);
  glLoadIdentity();
  glFlush();
}

void reshape(int w, int h)
{
  glViewport(0, 0, (GLsizei)w, (GLsizei)h);
  fAspect = (GLsizei)w / (GLsizei)h;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  // glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
  //gluOrtho2D(-5.0, 5.0, -5.0, 5.0);
  glOrtho(-5.0, 5.0, -5.0, 5.0, -1, 1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  if (perspectiva == 0)
  {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(angle, fAspect, -1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(left, rigth, lookAtAngle, 0, 0, 0, 0, 1, 0);
  }
}

void GerenciaTeclado(unsigned char key, int x, int y)
{
  switch (key)
  {
  case 'W':
  case 'w':
    left += 20;
    break;
  case 'A':
  case 'a':
    rigth -= 20;
    break;
  case 'S':
  case 's':
    left -= 20;
    break;
  case 'D':
  case 'd':
    rigth += 20;
    break;
  case 'Q':
  case 'q':
    lookAtAngle += 20;
    break;
  case 'E':
  case 'e':
    lookAtAngle -= 20;
    break;
  case 'F':
  case 'f':
    if (perspectiva == 1)
    {
      perspectiva = 0;
    }
    else
    {
      perspectiva = 1;
    }

    break;
  }
  reshape(800, 800);
  glutPostRedisplay();
}

void GerenciaMouse(int button, int state, int x, int y)
{

  if (button == GLUT_LEFT_BUTTON)
    if (state == GLUT_DOWN)
    { // Zoom-in
      if (angle >= 10)
        angle -= 5;
    }
  if (button == GLUT_RIGHT_BUTTON)
    if (state == GLUT_DOWN)
    { // Zoom-out
      if (angle <= 130)
        angle += 5;
    }
  reshape(800, 800);
  glutPostRedisplay();
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  angle = 45;
  lookAtAngle = 200;
  perspectiva = 1;
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(800, 800);
  glutInitWindowPosition(10, 10);
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMouseFunc(GerenciaMouse);
  glutKeyboardFunc(GerenciaTeclado);
  glutMainLoop();
  return 0;
}

// {{2, 3, 0}, {3, 2, 0}, {3, 4, 0}, {4, 3, 0}} = vertice1 + vertice2
