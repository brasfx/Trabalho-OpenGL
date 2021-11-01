#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

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
  // float vertices[3][3] = {{2, 3, 0}, {4, 3, 0}, {0, 2, 2}};
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  // eixo x
  glColor3f(1.0, 0.0, 0.0);
  linha(-40, 0, 0, 40, 0, 0, 4.0);
  // eixo y
  glColor3f(0.0, 1.0, 0.0);
  linha(0, -40, 0, 0, 40, 0, 4.0);
  glColor3f(0.0, 0.0, 1.0);
  triangulo(vertice1, GL_LINE_LOOP, 4);
  Translate(3, 2, 0);
  RotateZ(-180);
  // RotateY(90);
  // RotateX(90);
  Translate(-3, -2, 0);
  glColor3f(0.0, 0.0, 1.0);
  triangulo(vertice2, GL_LINE_LOOP, 4);
  // RotateZ(-45);
  Translate(1, -1, 0);
  glColor3f(1.0, 0.0, 0.0);
  quadrilatero(vertice3, GL_LINE_LOOP, 4);
  // Translate(2, -1, 0);
  // glColor3f(1.0, 0.0, 0.0);
  // quadrilatero(vertice3, GL_LINE_LOOP, 4);
  glLoadIdentity();
  glFlush();
}

void reshape(int w, int h)
{
  glViewport(0, 0, (GLsizei)w, (GLsizei)h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  // glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
  //glOrtho (-5.0, 5.0, -5.0, 5.0, 1.5, 20.0);
  gluOrtho2D(-5.0, 5.0, -5.0, 5.0);
  glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(800, 800);
  glutInitWindowPosition(10, 10);
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMainLoop();
  return 0;
}

// {{2, 3, 0}, {3, 2, 0}, {3, 4, 0}, {4, 3, 0}} = vertice1 + vertice2