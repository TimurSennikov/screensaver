#include <GLFW/glfw3.h>
#include <GL/gl.h>

float angle = 0.0f;
float positionX = 0.0f;
float positionY = 0.0f;
float size = 0.5f;
double xpos, ypos;

void drawBox() {
    // Set box color to white
    glColor3f(1.0f, 1.0f, 1.0f);

    // Draw a rotating box at the specified position
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);
    glRotatef(angle, 0.01f, 0.01f, 0.01f);

    // Draw the box manually
    glBegin(GL_LINES);

    // Bottom
    glVertex3f(-size, -size, -size);
    glVertex3f(size, -size, -size);

    glVertex3f(size, -size, -size);
    glVertex3f(size, -size, size);

    glVertex3f(size, -size, size);
    glVertex3f(-size, -size, size);

    glVertex3f(-size, -size, size);
    glVertex3f(-size, -size, -size);

    // Top
    glVertex3f(-size, size, -size);
    glVertex3f(size, size, -size);

    glVertex3f(size, size, -size);
    glVertex3f(size, size, size);

    glVertex3f(size, size, size);
    glVertex3f(-size, size, size);

    glVertex3f(-size, size, size);
    glVertex3f(-size, size, -size);

    // Vertical edges
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

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        // Rotate the box when arrow keys are pressed
        switch (key) {
            case GLFW_KEY_RIGHT:
                angle += 5.0f;
                break;
            case GLFW_KEY_LEFT:
                angle -= 5.0f;
                break;
            case GLFW_KEY_UP:
                size += 0.01f;
                break;
            case GLFW_KEY_DOWN:
                size -= 0.01f;
                break;
        }
    }
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(1920, 1080, "screensaver", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
	}

    glfwSetWindowAttrib(window, GLFW_FLOATING, GLFW_TRUE);

    // Make the window's context current
    glfwMakeContextCurrent(window);
	
    // glfwSetKeyCallback(window, keyCallback);

    glfwGetCursorPos(window, &xpos, &ypos);

    // Enable depth testing for 3D rendering
    glEnable(GL_DEPTH_TEST);
	
    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {
        // Render here
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw the rotating box at the specified position	
	drawBox();
        angle += 0.05f;
	// Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();

    return 0;
}

