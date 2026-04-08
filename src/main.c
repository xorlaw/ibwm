#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

Display *dpy;
Window root;
int running = 1;

void setup() {
    dpy = XOpenDisplay(NULL);
    if (!dpy) {
        fprintf(stderr, "Cannot open display\n");
        exit(1);
    }

    root = RootWindow(dpy, DefaultScreen(dpy));

    /* listen for new windows */
    XSelectInput(dpy, root, SubstructureRedirectMask | SubstructureNotifyMask);

    /* grab alt + q to quit */
    XGrabKey(dpy, XKeysymToKeycode(dpy, XK_q), Mod1Mask, root, True, GrabModeAsync, GrabModeAsync);

    XSync(dpy, False);
    printf("WM initialized successfully\n");
}

int main() {
    setup();
    printf("ready to handle windows\n");
    XCloseDisplay(dpy);
    return 0;
}


