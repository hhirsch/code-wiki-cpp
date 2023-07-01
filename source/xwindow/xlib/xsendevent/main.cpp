#include <X11/Xlib.h>
#include <X11/keysym.h>

#include <iostream>
#include <unistd.h>
#include <string.h>
#include <map>

using namespace std;

std::map<const char*, KeyCode> keyMap {
  {"ü", XK_udiaeresis},
  {"Ü", XK_Udiaeresis},
  {"ö", XK_odiaeresis},
  {"Ö", XK_Odiaeresis},
  {"ä", XK_adiaeresis},
  {"Ä", XK_Adiaeresis},
  {"ß", XK_ssharp},
  {"(", XK_braceleft},
  {")", XK_braceright},
  {"[", XK_bracketleft},
  {"]", XK_bracketright},
  {"<", XK_greater},
  {">", XK_less},
  {"{", XK_braceleft},
  {"}", XK_braceright}
};


KeyCode stringToKeysym(const char* character) {
  if (keyMap.count(character) != 0) {
    return keyMap.at(character);
  }

  return XStringToKeysym(character);
}

void sendKeyEvent(Display* display, const char* character) {
  XEvent event;
  XKeyEvent keyEvent;
  Window focusedWindow;
  int revertTo;
  XGetInputFocus(display, &focusedWindow, &revertTo);
  // Set up the event structure
  event.xkey.type = KeyPress;
  event.xkey.window = focusedWindow;
  event.xkey.display = display;
  event.xkey.state = 0;
  KeyCode keycode;
  keycode = XKeysymToKeycode(display, stringToKeysym(character));
  event.xkey.keycode = keycode;

  keyEvent = event.xkey;
  keyEvent.state = event.xkey.state;
  sleep(2);
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
  std::cout << "Keysim for a : " << (int)stringToKeysym("a") << std::endl;
  std::cout << "Keysim for { : " << (int)stringToKeysym("{") << std::endl;
  std::cout << "Value of constant for { : " << XK_braceleft << std::endl;
  sendKeyEvent(display, "a");
  return 0;
}
