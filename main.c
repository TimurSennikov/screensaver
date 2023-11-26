#include <stdio.h>
#include <X11/Xlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>

bool isAfk = false;
bool delay = false;
bool test = false;
float angle = 0.0f;
float size = 0.5f;
double xpos, ypos;

Display *display;
Window root;
XEvent ev;

void drawaBox() {
    glColor3f(1.0f, 1.0f, 1.0f);

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);
    glRotatef(angle, 0.01f, 0.01f, 0.01f);

    glBegin(GL_LINES);

    glVertex3f(-size, -size, -size);
    glVertex3f(size, -size, -size);

    glVertex3f(size, -size, -size);
    glVertex3f(size, -size, size);

    glVertex3f(size, -size, size);
    glVertex3f(-size, -size, size);

    glVertex3f(-size, -size, size);
    glVertex3f(-size, -size, -size);

    glVertex3f(-size, size, -size);
    glVertex3f(size, size, -size);

    glVertex3f(size, size, -size);
    glVertex3f(size, size, size);

    glVertex3f(size, size, size);
    glVertex3f(-size, size, size);

    glVertex3f(-size, size, size);
    glVertex3f(-size, size, -size);

    glVertex3f(-size, -size, -size);
    glVertex3f(-size, size, -size);

    glVertex3f(size, -size, -size);
    glVertex3f(size, size, -size);

    glVertex3f(size, -size, size);
    glVertex3f(size, size, size);

    glVertex3f(-size, -size, size);
    glVertex3f(-size, size, size);

    glEnd();

    glPopMatrix();
}

void drawawindow() {
        if (!glfwInit()) {
       	printf("failed to init glfw window");
    }
    
    GLFWwindow* window = glfwCreateWindow(1920, 1080, "screensaver", NULL, NULL);

    glfwSetWindowAttrib(window, GLFW_FLOATING, GLFW_TRUE);

    glfwMakeContextCurrent(window);

    glfwGetCursorPos(window, &xpos, &ypos);

    glEnable(GL_DEPTH_TEST);

	
    while (!glfwWindowShouldClose(window)) {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        drawaBox();
        angle += 0.05f;
        glfwSwapBuffers(window);

glfwPollEvents();
    }

   glfwTerminate();
}
int main() {
    unsigned int delaySeconds = 3;

    display = XOpenDisplay(0);

    if (!display) {
        fprintf(stderr, "Unable to open display\n");
        return 1;
    }

    root = DefaultRootWindow(display);

    while (1) {
        XQueryPointer(display, root, &ev.xbutton.root, &ev.xbutton.window,
                      &ev.xbutton.x_root, &ev.xbutton.y_root,
                      &ev.xbutton.x, &ev.xbutton.y,
                      &ev.xbutton.state);

        unsigned int oldxroot = ev.xbutton.x_root;
        unsigned int oldyroot = ev.xbutton.y_root;

        sleep(delaySeconds);

        XQueryPointer(display, root, &ev.xbutton.root, &ev.xbutton.window,
                      &ev.xbutton.x_root, &ev.xbutton.y_root,
                      &ev.xbutton.x, &ev.xbutton.y,
                      &ev.xbutton.state);

        unsigned int x = ev.xbutton.x_root;
        unsigned int y = ev.xbutton.y_root;

        if (oldxroot == x && oldyroot == y) {
            drawawindow();
             }
    }

    isAfk = false;
    XCloseDisplay(display);

    return 0;
}
