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

	for (std::map<char, std::string>::iterator iter = map.begin();
	     iter != map.end(); ++iter) {
		XGrabKey(dp, XKeysymToKeycode(dp, charToKeysym(iter->first)),
			 AnyModifier, root, 1, GrabModeAsync, GrabModeAsync);
	}

	Window win;

	bool shift = false;

	while (1) {
		int rev;
		XGetInputFocus(dp, &win, &rev);
		XSelectInput(dp, win, KeyPressMask | KeyReleaseMask);

		bool done = false;

		while (XPending(dp)) {
			XEvent evt;
			XNextEvent(dp, &evt);

			std::cout << evt.xkey.keycode << std::endl;

			if (evt.xkey.keycode == 50)
				shift = evt.type == KeyPress;
			if (evt.xkey.keycode == 9 && shift) {
				done = true;
				break;
			}

			std::map<char, std::string>::iterator res =
			    map.find(*XKeysymToString(evt.xkey.keycode));
			if (res != map.end())
				sendString(res->second, dp, win, root);
		}

		if (done)
			break;
	}

	XCloseDisplay(dp);

	return 0;
}
