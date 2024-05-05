#include <GL/freeglut.h>
#include <iostream>
#include <cmath>

int x = 20, y = 200, uplimit = 250;
int flag = 0;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2f(0, 400);
    glVertex2f(679, 400);
    glEnd();

    if (flag == 0)
    {
        y += 2;
        x += 1;
        if (y >= 385)
            flag = 1;
    }
    else if (flag == 1)
    {
        y -= 2;
        x += 1;
        if (y <= uplimit)
        {
            uplimit += 20;
            flag = 0;
        }
    }

    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < 360; i++)
    {
        float angle = i * 3.14159 / 180;
        float xPos = 15 * cos(angle);
        float yPos = 15 * sin(angle);
        glVertex2f(xPos, yPos);
    }
    glEnd();
    glPopMatrix();

    glutSwapBuffers();
}

void update(int value)
{
    glutPostRedisplay();
    glutTimerFunc(10, update, 0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(680, 400);
    glutCreateWindow("Bouncing Ball");

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 680, 0, 400);

    glutDisplayFunc(display);
    glutTimerFunc(10, update, 0);

    glutMainLoop();

    return 0;
}
