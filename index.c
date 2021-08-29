#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

void display(void)
{
  float vertices[4][3] = {{2, 3, 0}, {3, 2, 0}, {4, 3, 0}, {3, 4, 0}};
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  // eixo x
  glColor3f(1.0, 0.0, 0.0);
  // linha(-40, 0, 0, 40, 0, 0, 4.0);
  // eixo y
  glColor3f(0.0, 1.0, 0.0);
  // linha(0, -40, 0, 0, 40, 0, 4.0);
  glColor3f(0.0, 0.0, 0.0);
  // quadrilatero(vertices, GL_LINE_LOOP, 4);
  //   glTranslatef(3,2,0);
  // Translate(3, 2, 0);
  //   glRotatef(-30,0,0,1);
  // RotateZ(-30);
  //   glTranslatef(-3,-2,0);
  // Translate(-3, -2, 0);
  glColor3f(0.0, 0.0, 1.0);
  // quadrilatero(vertices, GL_LINE_LOOP, 4);
  glLoadIdentity();
  glFlush();
}

void reshape(int w, int h)
{
  glViewport(0, 0, (GLsizei)w, (GLsizei)h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  //glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
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