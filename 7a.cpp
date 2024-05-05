#include <GL/freeglut.h>
#include <cmath>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;
const int MAX_DEPTH = 1; // Maximum recursion depth for the snowflake

void drawKochSnowflake(float x1, float y1, float x2, float y2, int depth) {
    if (depth == 0) {
        // Base case: draw a line segment
        glBegin(GL_LINES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glEnd();
    } else {
        // Recursive case: divide the line segment into four parts and call the function recursively
        float deltaX = x2 - x1;
        float deltaY = y2 - y1;
        float x3 = x1 + deltaX / 3;
        float y3 = y1 + deltaY / 3;
        float x4 = x1 + 2 * deltaX / 3;
        float y4 = y1 + 2 * deltaY / 3;
        float x5 = (x3 + x4) / 2 + (y4 - y3) * sqrt(3) / 2;
        float y5 = (y3 + y4) / 2 + (x3 - x4) * sqrt(3) / 2;

        // Recursively draw the four line segments
        drawKochSnowflake(x1, y1, x3, y3, depth - 1);
        drawKochSnowflake(x3, y3, x5, y5, depth - 1);
        drawKochSnowflake(x5, y5, x4, y4, depth - 1);
        drawKochSnowflake(x4, y4, x2, y2, depth - 1);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0); // Set color to white

    float centerX = WINDOW_WIDTH / 2;
    float centerY = WINDOW_HEIGHT / 2;
    float radius = WINDOW_HEIGHT / 3;

    // Calculate the initial coordinates of the Koch snowflake triangle
    float x1 = centerX - radius * sqrt(3) / 2;
    float y1 = centerY - radius / 2;
    float x2 = centerX + radius * sqrt(3) / 2;
    float y2 = y1;
    float x3 = centerX;
    float y3 = centerY + radius;

    // Draw the three line segments of the initial triangle
    drawKochSnowflake(x1, y1, x2, y2, MAX_DEPTH);
    drawKochSnowflake(x2, y2, x3, y3, MAX_DEPTH);
    drawKochSnowflake(x3, y3, x1, y1, MAX_DEPTH);

    glFlush();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Koch Snowflake");
    glClearColor(0.0, 0.0, 0.0, 1.0); // Set clear color to black
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
