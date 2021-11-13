#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

GLfloat angle, fAspect, UpDown, LeftRight, Forward;
GLfloat ambientLight[] = {0.3, 0.3, 0.3, 1.0};
GLfloat difuse[] = {0.7, 0.7, 0.7, 1.0};
GLfloat especular[] = {0.3, 0.3, 0.3, 1.0};
GLfloat lightPosition[] = {-5.0, 5.0, -5.0, 1.0};
GLfloat brilho[] = {50.0};
GLfloat gray[] = {0.75, 0.75, 0.75, 1.0};
GLfloat spec[] = {0.0, 0.0, 0.0, 1.0};
GLint perspectiva;

float *normaliza(float *v)
{
  float *normalizado;
  normalizado = (float *)malloc(3 * sizeof(float));
  float raiz = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
  for (int i = 0; i < 3; i++)
  {
    normalizado[i] = normalizado[i] / raiz;
  }
  return normalizado;
}

float *produto(float *v1, float *v2)
{
  float *resultadop;
  resultadop = (float *)malloc(3 * sizeof(float));
  resultadop[0] = v1[1] * v2[2] - v1[2] * v2[1];
  resultadop[1] = -(v1[0] * v2[2] - v1[2] * v2[0]);
  resultadop[2] = v1[0] * v2[1] - v1[1] * v2[0];

  resultadop = normaliza(resultadop);
  return resultadop;
}

float *Normal(float *v1, float *v2, float *v3)
{
  float *vetor;
  vetor = (float *)(3 * sizeof(float));
  float x[] = {v2[0] - v1[0], v2[1] - v1[1], v2[2] - v1[2]};

  float y[] = {v3[0] - v1[0], v3[1] - v1[1], v3[2] - v1[2]};

  vetor = produto(x, y);

  return vetor;
}

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

void poligono3d(float verts[16][3], float espessura)
{
  glLineWidth(espessura);
  glBegin(GL_TRIANGLE_FAN);
  glNormal3fv(Normal(verts[0], verts[1], verts[2]));
  for (int i = 0; i < 8; i++)
  {
    glVertex3fv(verts[i]);
  }
  glEnd();
  glBegin(GL_TRIANGLE_FAN);
  glNormal3fv(Normal(verts[0], verts[2], verts[1]));
  for (int i = 8; i < 16; i++)
  {
    glVertex3fv(verts[i]);
  }
  glEnd();
  glBegin(GL_TRIANGLES);
  for (int i = 0; i < 7; i++)
  {

    glNormal3fv(Normal(verts[i+8], verts[i + 1], verts[i]));
    glVertex3fv(verts[i]);
    glVertex3fv(verts[i + 1]);
    glVertex3fv(verts[i + 8]);
    glVertex3fv(verts[i + 1]);
    glVertex3fv(verts[i + 8]);
    glVertex3fv(verts[i + 9]);
  }

  glNormal3fv(Normal(verts[15], verts[0], verts[7]));

  glVertex3fv(verts[7]);
  glVertex3fv(verts[0]);
  glVertex3fv(verts[15]);
  glVertex3fv(verts[0]);
  glVertex3fv(verts[15]);
  glVertex3fv(verts[8]);

  glEnd();
}

void triangulo3d(float verts[6][3], float espessura)
{
  glLineWidth(espessura);
  glBegin(GL_TRIANGLES);
  glNormal3fv(Normal(verts[2], verts[1], verts[0]));
  for (int i = 0; i < 3; i++)
  {
    glVertex3fv(verts[i]);
  }
  glEnd();
  glBegin(GL_TRIANGLES);
  glNormal3fv(Normal(verts[5], verts[4], verts[3]));
  for (int i = 3; i < 6; i++)
  {

    glVertex3fv(verts[i]);
  }
  glEnd();

  glBegin(GL_TRIANGLES);
  glNormal3fv(Normal(verts[3], verts[1], verts[0]));
  glVertex3fv(verts[0]);
  glVertex3fv(verts[1]);
  glVertex3fv(verts[3]);
  glVertex3fv(verts[1]);
  glVertex3fv(verts[3]);
  glVertex3fv(verts[4]);

  glNormal3fv(Normal(verts[4], verts[2], verts[1]));
  glVertex3fv(verts[1]);
  glVertex3fv(verts[2]);
  glVertex3fv(verts[4]);
  glVertex3fv(verts[2]);
  glVertex3fv(verts[4]);
  glVertex3fv(verts[5]);

  glNormal3fv(Normal(verts[5], verts[2], verts[1]));
  glVertex3fv(verts[2]);
  glVertex3fv(verts[1]);
  glVertex3fv(verts[5]);
  glVertex3fv(verts[1]);
  glVertex3fv(verts[5]);
  glVertex3fv(verts[3]);
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
  //2d triangulo
  float vertice1[3][3] = {{2, 3, 0}, {3, 2, 0}, {4, 3, 0}};
  float vertice2[3][3] = {{2, 3, 0}, {3, 2, 0}, {4, 3, 0}};
  //3d triangulo
  float vertice3[6][3] = {{2, 3, 0}, {3, 2, 0}, {4, 3, 0}, {2, 3, 1}, {3, 2, 1}, {4, 3, 1}};
  float vertice4[6][3] = {{2, 3, 0}, {3, 2, 0}, {4, 3, 0}, {2, 3, 1}, {3, 2, 1}, {4, 3, 1}};
  //2d Concavo
  float vertices[8][3] = {{3, 1, 0}, {3, 2, 0}, {3, 3, 0}, {2, 3, 0}, {2, 2, 0}, {1, 2, 0}, {1, 1, 0}, {2, 1, 0}};
  float vertices2[8][3] = {{3, 1, 0}, {3, 2, 0}, {3, 3, 0}, {2, 3, 0}, {2, 2, 0}, {1, 2, 0}, {1, 1, 0}, {2, 1, 0}};
  //3d Concavo
  float vertices3[16][3] = {{3, 1, 0}, {3, 2, 0}, {3, 3, 0}, {2, 3, 0}, {2, 2, 0}, {1, 2, 0}, {1, 1, 0}, {2, 1, 0}, {3, 1, 1}, {3, 2, 1}, {3, 3, 1}, {2, 3, 1}, {2, 2, 1}, {1, 2, 1}, {1, 1, 1}, {2, 1, 1}};
  float vertices4[16][3] = {{3, 1, 0}, {3, 2, 0}, {3, 3, 0}, {2, 3, 0}, {2, 2, 0}, {1, 2, 0}, {1, 1, 0}, {2, 1, 0}, {3, 1, 1}, {3, 2, 1}, {3, 3, 1}, {2, 3, 1}, {2, 2, 1}, {1, 2, 1}, {1, 1, 1}, {2, 1, 1}};


  glShadeModel(GL_SMOOTH);
  glEnable(GL_NORMALIZE);
  //glClearColor(1.0, 1.0, 1.0, 0.0);

  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray);
  glEnable(GL_COLOR_MATERIAL);
  glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, ambientLight);
  glEnable(GL_LIGHT1);
  
  glMaterialfv(GL_FRONT, GL_SPECULAR, spec);
  glMateriali(GL_FRONT,GL_SHININESS,20);
  glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, difuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, especular);
  glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  
   glEnable(GL_DEPTH_TEST);
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColor3f(0.5, 0.5, 0.0);
  Translate(-3, 0, 0);
  //triangulo(vertice1, GL_TRIANGLES, 4);
  triangulo3d(vertice3, 4);
  Translate(3, 2, 0);
  RotateZ(-180);
  Translate(-3, -2, 0);
  glColor3f(0.0, 1.0, 0.0);
  //triangulo(vertice2, GL_TRIANGLES, 4);
  triangulo3d(vertice4, 4);
  glColor3f(1.0, 0.0, 0.0);
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
  //poligono(vertices, GL_TRIANGLE_FAN, 2);
  poligono3d(vertices3, 2);
  RotateZ(180);
  Translate(-1.91, -6.12, 0);
  //poligono(vertices2, GL_TRIANGLE_FAN, 2);
  poligono3d(vertices4, 2);
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
    gluLookAt(LeftRight, UpDown, Forward, 0, 0, 0, 0, 1, 0);
  }
}

void GerenciaTeclado(unsigned char key, int x, int y)
{
  switch (key)
  {
  case 'W':
  case 'w':
    UpDown += 20;
    break;
  case 'A':
  case 'a':
    LeftRight -= 20;
    break;
  case 'S':
  case 's':
    UpDown -= 20;
    break;
  case 'D':
  case 'd':
    LeftRight += 20;
    break;
  case 'Q':
  case 'q':
    Forward += 20;
    break;
  case 'E':
  case 'e':
    Forward -= 20;
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
  Forward = 200;
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
