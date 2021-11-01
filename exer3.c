#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define ESPESSURA_PADRAO 2.0
#define ESPESSURA_EIXOS 4.0

void imprimirMatriz(float matriz[4][4])
{
   printf("\n");
   for (int i = 0; i < 4; i++)
   {
      for (int j = 0; j < 4; j++)
      {
         printf("%f ", matriz[i][j]);
      }
      printf("\n");
   }
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

void linha(float x1, float y1, float z1, float x2, float y2, float z2, float espessura)
{
   glLineWidth(espessura);
   glBegin(GL_LINES);
   glVertex3f(x1, y1, z1);
   glVertex3f(x2, y2, z2);
   glEnd();
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

void display(void)
{
   float poligono[4][3] = {{0.5, 0.5, 0.5}, {0.5, 0.5, -0.5}, {0.5, -0.5, -0.5}, {0.5, -0.5, 0.5}};
   glClearColor(1.0, 1.0, 1.0, 0.0);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glEnable(GL_DEPTH_TEST);
   glLoadIdentity();
   gluLookAt(5, 7, 5, 0, 0, 0, 0, 1, 0);
   glColor3f(1.0, 0.0, 0.0);
   linha(-40, 0, 0, 40, 0, 0, ESPESSURA_EIXOS);
   glColor3f(0.0, 1.0, 0.0);
   linha(0, -40, 0, 0, 40, 0, ESPESSURA_EIXOS);
   glColor3f(0.0, 0.0, 1.0);
   linha(0, 0, -40, 0, 0, 40, ESPESSURA_EIXOS);
   glLineWidth(ESPESSURA_PADRAO);
   glColor3f(0.0, 0.0, 0.0);
   Scale(3.0 / 5.0, 5.0 / 3.0, 1.0);
   RotateY(-90);
   RotateZ(90);
   Translate(1.5, -0.5, 2.5);
   Scale(3.0, 1.0, 5.0);
   quadrilatero(poligono, GL_POLYGON, ESPESSURA_PADRAO);
   glutWireCube(1);
   glFlush();
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei)w, (GLsizei)h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glFrustum(-1.5, 1.5, -1.5, 1.5, 1, 20);
   glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(400, 400);
   glutInitWindowPosition(10, 10);
   glutCreateWindow(argv[0]);
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutMainLoop();
   return 0;
}