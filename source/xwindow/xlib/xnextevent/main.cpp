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
      // If you convert to hex you will notice that these  are different from the hex keycodes and
      // states in /usr/include/X11/keysymdef.h
      // You need "XLookupKeysym"" or "XKeycodeToKeysym" to convert them
      std::cout << "Key Press" << std::endl;
    } else if (event.type == KeyRelease) {
      std::cout << "Key Release" << std::endl;
    }
    if (event.type == KeyPress || event.type == KeyRelease) {
      std::cout << "keycode=" << event.xkey.keycode << ", state=" << event.xkey.state << std::endl;
      KeySym keysymKey;
      keysymKey = XKeycodeToKeysym(display, event.xkey.keycode, 0);
      if (keysymKey != NoSymbol) {
        std::cout << "Keysym Keycode: " << XKeysymToString(keysymKey) << std::endl;
      }

      KeySym keysymState;
      keysymState = XKeycodeToKeysym(display, event.xkey.state, 0);
      if (keysymState != NoSymbol) {
        std::cout << "Keysym State: " << XKeysymToString(keysymState) << std::endl;
      }
      std::cout << std::endl << std::endl;
    }
  }

  XCloseDisplay(display);
  return 0;
}
