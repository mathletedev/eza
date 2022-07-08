#ifndef KEYS_H
#define KEYS_H

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <iostream>

KeySym charToKeysym(char c);

XKeyEvent createKeyEvent(Display *dp, Window &win, Window &root, bool down,
			 int kc, int mod);

void sendString(std::string s, Display *dp, Window &win, Window &root);

#endif
