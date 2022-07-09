#include "keys.h"
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <iostream>
#include <map>

int main() {
	Display *dp = XOpenDisplay(NULL);
	if (!dp)
		return 1;

	std::map<char, std::string> map;
	map['a'] = "bag";

	Window root = XDefaultRootWindow(dp);

	grabAll(map, dp, root);

	Window win;

	std::map<unsigned int, int> keys;
	bool shift = false;

	while (1) {
		int rev;
		XGetInputFocus(dp, &win, &rev);
		XSelectInput(dp, win, KeyPressMask | KeyReleaseMask);

		bool done = false;

		while (XPending(dp)) {
			XEvent evt;
			XNextEvent(dp, &evt);

			if (evt.xkey.keycode == 50)
				shift = evt.type == KeyPress;
			if (evt.xkey.keycode == 9 && shift) {
				done = true;
				break;
			}

			if (evt.type != KeyPress)
				break;

			if (!keys[evt.xkey.keycode])
				keys[evt.xkey.keycode] = 0;

			std::map<char, std::string>::iterator res =
			    map.find(*XKeysymToString(evt.xkey.keycode));

			if (res != map.end() && keys[evt.xkey.keycode] == 0) {
				ungrabAll(map, dp, root);
				sendString(res->second, &keys, dp, win, root);
				grabAll(map, dp, root);
			} else if (keys[evt.xkey.keycode] > 0)
				keys[evt.xkey.keycode]--;
		}

		if (done)
			break;
	}

	XCloseDisplay(dp);

	return 0;
}
