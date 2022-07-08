#include "keys.h"

KeySym charToKeysym(char c) {
	switch (c) {
	case ' ':
		return XK_space;
	case '1':
		return XK_1;
	case '2':
		return XK_2;
	case '3':
		return XK_3;
	case '4':
		return XK_4;
	case '5':
		return XK_5;
	case '6':
		return XK_6;
	case '7':
		return XK_7;
	case '8':
		return XK_8;
	case '9':
		return XK_9;
	case '0':
		return XK_0;
	case 'A':
		return XK_A;
	case 'B':
		return XK_B;
	case 'C':
		return XK_C;
	case 'D':
		return XK_D;
	case 'E':
		return XK_E;
	case 'F':
		return XK_F;
	case 'G':
		return XK_G;
	case 'H':
		return XK_H;
	case 'I':
		return XK_I;
	case 'J':
		return XK_J;
	case 'K':
		return XK_K;
	case 'L':
		return XK_L;
	case 'M':
		return XK_M;
	case 'N':
		return XK_N;
	case 'O':
		return XK_O;
	case 'P':
		return XK_P;
	case 'Q':
		return XK_Q;
	case 'R':
		return XK_R;
	case 'S':
		return XK_S;
	case 'T':
		return XK_T;
	case 'U':
		return XK_U;
	case 'V':
		return XK_V;
	case 'W':
		return XK_W;
	case 'X':
		return XK_X;
	case 'Y':
		return XK_Y;
	case 'Z':
		return XK_Z;
	case 'a':
		return XK_a;
	case 'b':
		return XK_b;
	case 'c':
		return XK_c;
	case 'd':
		return XK_d;
	case 'e':
		return XK_e;
	case 'f':
		return XK_f;
	case 'g':
		return XK_g;
	case 'h':
		return XK_h;
	case 'i':
		return XK_i;
	case 'j':
		return XK_j;
	case 'k':
		return XK_k;
	case 'l':
		return XK_l;
	case 'm':
		return XK_m;
	case 'n':
		return XK_n;
	case 'o':
		return XK_o;
	case 'p':
		return XK_p;
	case 'q':
		return XK_q;
	case 'r':
		return XK_r;
	case 's':
		return XK_s;
	case 't':
		return XK_t;
	case 'u':
		return XK_u;
	case 'v':
		return XK_v;
	case 'w':
		return XK_w;
	case 'x':
		return XK_x;
	case 'y':
		return XK_y;
	case 'z':
		return XK_z;
	default:
		return 0;
	}
}

XKeyEvent createKeyEvent(Display *dp, Window &win, Window &root, bool down,
			 int kc, int mod) {
	XKeyEvent event;

	event.display = dp;
	event.window = win;
	event.root = root;
	event.subwindow = None;
	event.time = CurrentTime;
	event.x = 1;
	event.y = 1;
	event.x_root = 1;
	event.y_root = 1;
	event.same_screen = 1;
	event.keycode = kc;
	event.state = mod;
	event.type = down ? KeyPress : KeyRelease;

	return event;
}

void sendString(std::string s, Display *dp, Window &win, Window &root) {
	for (char &c : s) {
		XKeyEvent evt =
		    createKeyEvent(dp, win, root, true,
				   XKeysymToKeycode(dp, charToKeysym(c)), 0);
		XSendEvent(evt.display, evt.window, 1, KeyPressMask,
			   (XEvent *)&evt);
		evt = createKeyEvent(dp, win, root, false,
				     XKeysymToKeycode(dp, charToKeysym(c)), 0);
		XSendEvent(evt.display, evt.window, 1, KeyPressMask,
			   (XEvent *)&evt);
	}
}
