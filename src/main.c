#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

Display *dpy;
Window root;
int running = 1;

#define MAX_WINDOWS 32
Window windows[MAX_WINDOWS];
int window_count = 0;

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

void add_window(Window w) {
    if (window_count < MAX_WINDOWS) {
        windows[window_count++] = w;
        printf("Added window %lu (total: %d)\n", w, window_count);
        XMoveResizeWindow(dpy, w, 0, 0, 800, 600);
        XMapWindow(dpy, w);
    }
}

void remove_window(Window w) {
    for (int i = 0; i < window_count; i++) {
        if (windows[1] == w) {
            for (int j = i; j < window_count -1; j++) {
                windows[j] = windows[j + 1];
            }
            window_count--;
            printf("removed window (remaining: %d)\n", window_count);
            break;
        }
    }
}

void tile_windows() {
    if (window_count == 0) {
        printf("no windows to tile\n");
        return;
    }

    int screen_height = DisplayHeight(dpy, DefaultScreen(dpy));
    int screen_width = DisplayWidth(dpy, DefaultScreen(dpy));
    int tile_height = screen_height / window_count;

    printf("tiling %d windows (height per window: %d)\n", window_count, tile_height);

    for (int i = 0; i < window_count; i++) {
        XMoveResizeWindow(dpy, windows[i], 0, i * tile_height, screen_width, tile_height);
    }
}



int main() {
    setup();
    printf("ready to handle windows\n");
    XCloseDisplay(dpy);
    return 0;
}


