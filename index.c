#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <SOIL/SOIL.h>
// #define STB_IMAGE_IMPLEMENTATION
// #include <stb_image.h>

GLfloat angle, fAspect, UpDown, LeftRight, Forward;
GLfloat ambientLight[] = {0.3, 0.3, 0.3, 1.0};
GLfloat difuse[] = {0.7, 0.7, 0.7, 1.0};
GLfloat especular[] = {0.3, 0.3, 0.3, 1.0};
GLfloat lightPosition[] = {-5.0, 5.0, -5.0, 0.0};
GLfloat brilho[] = {50.0};
GLfloat gray[] = {0.75, 0.75, 0.75, 1.0};
GLfloat spec[] = {1.0, 1.0, 1.0, 1.0};
GLint perspectiva;
GLuint texture[1];
unsigned char *image;

void setPixel(int x, int y, int z)
{
  glBegin(GL_POINTS);
  glVertex3i(x, y, z);
  glEnd();
  glFlush();
}

void DDAXY(int x1, int y1, int x2, int y2)
{
  float length;
  float x, y, dx, dy;
  if (abs(y2 - y1) > abs(x2 - x1))
  {
    length = abs(y2 - y1);
  }
  else
  {
    length = abs(x2 - x1);
  }
  dx = (x2 - x1) / length;
  dy = (y2 - y1) / length;
  x = x1;
  y = y1;
  for (int i = 0; i < length; i++)
  {
    setPixel(round(x), round(y), 0);
    x = x + dx;
    y = y + dy;
  }
}

void DDAXZ(int x1, int z1, int x2, int z2)
{
  float length;
  float x, z, dx, dz;
  if (abs(z2 - z1) > abs(x2 - x1))
  {
    length = abs(z2 - z1);
  }
  else
  {
    length = abs(x2 - x1);
  }
  dx = (x2 - x1) / length;
  dz = (z2 - z1) / length;
  x = x1;
  z = z1;
  for (int i = 0; i < length; i++)
  {
    setPixel(round(x), 0, round(z));
    x = x + dx;
    z = z + dz;
  }
}

void DDAYZ(int y1, int z1, int y2, int z2)
{
  float length;
  float y, z, dy, dz;
  if (abs(z2 - z1) > abs(y2 - y1))
  {
    length = abs(z2 - z1);
  }
  else
  {
    length = abs(y2 - y1);
  }
  dy = (y2 - y1) / length;
  dz = (z2 - z1) / length;
  y = y1;
  z = z1;
  for (int i = 0; i < length; i++)
  {
    setPixel(0, round(y), round(z));
    y = y + dy;
    z = z + dz;
  }
}

void DDAXYZ(int x1, int y1, int z1, int x2, int y2, int z2)
{
  float length;
  float x, y, z, dx, dy, dz;
  length = abs(x2 - x1);
  if (abs(z2 - z1) > abs(y2 - y1) && abs(z2 - z1) > abs(y2 - y1))
  {
    length = abs(z2 - z1);
  }
  if (abs(y2 - y1) > abs(x2 - x1) && abs(y2 - y1) > abs(z2 - z1))
  {
    length = abs(y2 - y1);
  }
  dx = (x2 - x1) / length;
  dy = (y2 - y1) / length;
  dz = (z2 - z1) / length;
  x = x1;
  y = y1;
  z = z1;
  for (int i = 0; i < length; i++)
  {
    setPixel(round(x), round(y), round(z));
    x = x + dx;
    y = y + dy;
    z = z + dz;
  }
}

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
  glNormal3fv(Normal(verts[2], verts[0], verts[1]));
  for (int i = 8; i < 16; i++)
  {
    glVertex3fv(verts[i]);
  }
  glEnd();
  glBegin(GL_TRIANGLES);
  for (int i = 0; i < 7; i++)
  {

    glNormal3fv(Normal(verts[i + 8], verts[i + 1], verts[i]));
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
  glBindTexture(GL_TEXTURE_2D, texture[0]);
  glBegin(GL_TRIANGLES);
  glNormal3fv(Normal(verts[0], verts[1], verts[3]));
  glVertex3fv(verts[0]);
  glVertex3fv(verts[1]);
  glVertex3fv(verts[3]);
  glVertex3fv(verts[1]);
  glVertex3fv(verts[3]);
  glVertex3fv(verts[4]);

  glNormal3fv(Normal(verts[1], verts[2], verts[4]));
  glVertex3fv(verts[1]);
  glVertex3fv(verts[2]);
  glVertex3fv(verts[4]);
  glVertex3fv(verts[2]);
  glVertex3fv(verts[4]);
  glVertex3fv(verts[5]);

  glNormal3fv(Normal(verts[0], verts[3], verts[5]));
  glVertex3fv(verts[0]);
  glVertex3fv(verts[3]);
  glVertex3fv(verts[5]);
  glVertex3fv(verts[2]);
  glVertex3fv(verts[5]);
  glVertex3fv(verts[0]);
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
  matriz[2][2] = sz;
  Transposta(matriz);
  glMultMatrixf((float *)matriz);
}

void display(void)
{

  float triangulo1[6][3] = {{0, 2.1, 0}, {2, 2.1, 0}, {2, 4.1, 0}, {0, 2.1, 1}, {2, 2.1, 1}, {2, 4.1, 1}};
  float triangulo2[6][3] = {{2.1, 2, 0}, {2.1, 0, 0}, {4.1, 2, 0}, {2.1, 2, 1}, {2.1, 0, 1}, {4.1, 2, 1}};
  float concavo1[16][3] = {{0, 0, 0}, {1, 0, 0}, {2, 0, 0}, {2, 1, 0}, {1, 1, 0}, {1, 2, 0}, {0, 2, 0}, {0, 1, 0}, {0, 0, 1}, {1, 0, 1}, {2, 0, 1}, {2, 1, 1}, {1, 1, 1}, {1, 2, 1}, {0, 2, 1}, {0, 1, 1}};
  float concavo2[16][3] = {{4.1, 4.1, 0}, {3.1, 4.1, 0}, {2.1, 4.1, 0}, {2.1, 3.1, 0}, {3.1, 3.1, 0}, {3.1, 2.1, 0}, {4.1, 2.1, 0}, {4.1, 3.1, 0}, {4.1, 4.1, 1}, {3.1, 4.1, 1}, {2.1, 4.1, 1}, {2.1, 3.1, 1}, {3.1, 3.1, 1}, {3.1, 2.1, 1}, {4.1, 2.1, 1}, {4.1, 3.1, 1}};
  glShadeModel(GL_SMOOTH);
  glEnable(GL_NORMALIZE);
  //glClearColor(1.0, 1.0, 1.0, 0.0);

  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray);
  glEnable(GL_COLOR_MATERIAL);
  glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

  glLightfv(GL_LIGHT1, GL_DIFFUSE, ambientLight);
  glEnable(GL_LIGHT1);

  glLightfv(GL_LIGHT2, GL_SPECULAR, especular);
  glEnable(GL_LIGHT2);

  glMaterialfv(GL_FRONT, GL_SPECULAR, spec);
  glMateriali(GL_FRONT, GL_SHININESS, 128);
  glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, difuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, especular);
  glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  glEnable(GL_DEPTH_TEST);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColor3f(0.5, 0.5, 0.0);
  DDAXYZ(0, 2, 1, 3, 5, 8);
  Scale(2, 2, 2);
  Translate(-2.05, -2.05, 0);
  RotateZ(-45);

  triangulo3d(triangulo1, 4);
  glColor3f(0.0, 1.0, 0.0);

  triangulo3d(triangulo2, 4);
  glColor3f(1.0, 0.0, 0.0);

  poligono3d(concavo1, 2);
  glColor3f(0.0, 0.0, 1.0);

  poligono3d(concavo2, 2);
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

void geraTextura(int width, int height)
{
  glEnable(GL_TEXTURE_2D);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  //image = stbi_load("textura.jpg", &width, &height, 3, 0);
  glGenTextures(1, texture);
  //glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture[0]);
  image = SOIL_load_image("textura.jpg", &width, &height, 0, SOIL_LOAD_RGB);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
  //glGenerateMipMaps(GL_TEXTURE_2D);

  // stbi_image_free(texture);
  glBindTexture(GL_TEXTURE_2D, 0);

  SOIL_free_image_data(image);
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
  geraTextura(4, 4);
  return 0;
}

// {{2, 3, 0}, {3, 2, 0}, {3, 4, 0}, {4, 3, 0}} = vertice1 + vertice2
