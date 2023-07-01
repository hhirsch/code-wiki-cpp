#include <X11/Xlib.h>
#include <X11/keysym.h>

#include <iostream>
#include <unistd.h>
#include <string.h>
#include <map>

using namespace std;

// Code demonstrates raw keycode and state

void sendKeyPressEvent(Display* display, int code, int state) {
  XEvent event;
  XKeyEvent keyEvent;
  Window focusedWindow;
  int revertTo;
  XGetInputFocus(display, &focusedWindow, &revertTo);
  // Set up the event structure
  event.xkey.type = KeyPress;
  event.xkey.window = focusedWindow;
  event.xkey.display = display;
  event.xkey.state = state;
  event.xkey.keycode = code;

  // Send the event
  XSendEvent(display, event.xkey.window, True, KeyPressMask, &event);
  XFlush(display);
}

void sendKeyReleaseEvent(Display* display, int code, int state) {
  XEvent event;
  XKeyEvent keyEvent;
  Window focusedWindow;
  int revertTo;
  XGetInputFocus(display, &focusedWindow, &revertTo);
  // Set up the event structure
  event.xkey.type = KeyPress;
  event.xkey.window = focusedWindow;
  event.xkey.display = display;
  event.xkey.state = state;
  event.xkey.keycode = code;

  // Send the event
  XSendEvent(display, event.xkey.window, True, KeyPressMask, &event);
  XFlush(display);
}

int main() {
  Display* display = XOpenDisplay(NULL);
  if (display == NULL){
    printf("Error: Unable to connect to X11\n");
    return 1;
  }
  sendKeyPressEvent(display, 44, 128); // Mod3 + n = (
  return 0;
}
