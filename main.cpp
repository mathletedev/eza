#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <iostream>

XKeyEvent createKeyEvent(Display *display, Window &window, Window &root,
                         bool down, int keycode, int modifiers) {
  XKeyEvent event;

  event.display = display;
  event.window = window;
  event.root = root;
  event.subwindow = None;
  event.time = CurrentTime;
  event.x = 1;
  event.y = 1;
  event.x_root = 1;
  event.y_root = 1;
  event.same_screen = True;
  event.keycode = keycode;
  event.state = modifiers;
  event.type = down ? KeyPress : KeyRelease;

  return event;
}

int main() {
  Display *display = XOpenDisplay(NULL);
  if (!display)
    return 1;

  Window root = XDefaultRootWindow(display);
  int revert;

  Window window;
  XGetInputFocus(display, &window, &revert);
  XKeyEvent event = createKeyEvent(display, window, root, true, 26, 0);
  XSendEvent(event.display, event.window, 1, KeyPressMask, (XEvent *)&event);
  event = createKeyEvent(display, window, root, false, 26, 0);
  XSendEvent(event.display, event.window, 1, KeyPressMask, (XEvent *)&event);
  XFlush(display);

  int keycode = XKeysymToKeycode(display, XK_a);
  int rv = XGrabKey(display, keycode, AnyModifier, root, 1, GrabModeAsync,
                    GrabModeAsync);
  std::cout << rv << std::endl;

  XSelectInput(display, window, KeyPressMask | KeyReleaseMask);
  while (1) {
    while (XPending(display)) {
      XEvent event;
      XNextEvent(display, &event);
      uint32_t keycode = event.xkey.keycode;
      std::cout << keycode << std::endl;
    }
  }

  XCloseDisplay(display);

  return 0;
}
