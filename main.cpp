#include "keys.h"
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <iostream>
#include <map>

int main() {
  Display *dp = XOpenDisplay(NULL);
  if (!dp)
    return 1;

  std::map<char, std::string> map;
  map['a'] = "hello";

  Window root = XDefaultRootWindow(dp);
  int rev;

  Window win;
  XGetInputFocus(dp, &win, &rev);
  /* XKeyEvent event = createKeyEvent(display, window, root, true, 26, 0); */
  /* XSendEvent(event.display, event.window, 1, KeyPressMask, (XEvent *)&event);
   */
  /* event = createKeyEvent(display, window, root, false, 26, 0); */
  /* XSendEvent(event.display, event.window, 1, KeyPressMask, (XEvent *)&event);
   */
  /* XFlush(display); */

  for (std::map<char, std::string>::iterator iter = map.begin();
       iter != map.end(); ++iter) {
    XGrabKey(dp, XKeysymToKeycode(dp, charToKeysym(iter->first)), AnyModifier,
             root, 1, GrabModeAsync, GrabModeAsync);
  }

  XSelectInput(dp, win, KeyPressMask | KeyReleaseMask);
  while (1) {
    while (XPending(dp)) {
      XEvent evt;
      XNextEvent(dp, &evt);
      std::map<char, std::string>::iterator res =
          map.find(*XKeysymToString(evt.xkey.keycode));
      if (res != map.end())
        sendString(res->second, dp, win, root);
    }
  }

  XCloseDisplay(dp);

  return 0;
}
