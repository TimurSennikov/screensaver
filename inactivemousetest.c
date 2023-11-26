#include <stdio.h>
#include <X11/Xlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>

bool isAfk = false;
bool delay = false;
bool test = false;

int main() {
    Display *display;
    Window root;
    XEvent ev;
    unsigned int delaySeconds = 600;

    display = XOpenDisplay(NULL);

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
            system("./screensaver");
            // Additional actions you may want to perform when the mouse is idle
        }
    }

    isAfk = false;
    XCloseDisplay(display);

    return 0;
}

