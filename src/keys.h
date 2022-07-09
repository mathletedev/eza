#ifndef KEYS_H
#define KEYS_H

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <iostream>
#include <map>

KeySym charToKeysym(char c);

XKeyEvent createKeyEvent(Display *dp, Window &win, Window &root, bool down,
			 int kc, int mod);

void sendString(std::string s, std::map<unsigned int, int> *keys, Display *dp,
		Window &win, Window &root);

void grabAll(std::map<char, std::string> map, Display *dp, Window root);

void ungrabAll(std::map<char, std::string> map, Display *dp, Window root);

#endif
