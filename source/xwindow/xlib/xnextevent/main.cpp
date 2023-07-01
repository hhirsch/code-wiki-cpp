#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <iomanip>

int main() {
  Display* display = XOpenDisplay(NULL);
  Window rootWindow = DefaultRootWindow(display);
  std::cout << "Initialized" << std::endl;
  // Enable KeyPress and KeyRelease events on the root window
  Window focusedWindow;
  int revertTo;
  XGetInputFocus(display, &focusedWindow, &revertTo);

  XSelectInput(display, focusedWindow, KeyPressMask | KeyReleaseMask);

  while(1) {
    XEvent event;
    XNextEvent(display, &event);
    if (event.type == KeyPress) {
      // Log the key press event
      // If you convert to hex you will notice that these  are different from the hex keycodes and
      // states in /usr/include/X11/keysymdef.h
      // You need "XLookupKeysym"" or "XKeycodeToKeysym" to convert them
      printf("Key Press: keycode=%u, state=%u\n", event.xkey.keycode, event.xkey.state);
    } else if (event.type == KeyRelease) {
      // Log the key release event
      printf("Key Release: keycode=%u, state=%u\n", event.xkey.keycode, event.xkey.state);
    }
  }

  XCloseDisplay(display);
  return 0;
}
