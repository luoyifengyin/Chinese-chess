#pragma once
#include "head.h"
#include <string>
#define ButtonColor LIGHTGRAY

class Button {
protected:
	mutable CRect r;
	string str;
public:
	Button(int x, int y, const string& s) :r(x, y, x + ButtonWidth, y + ButtonHeight), str(s) {}
	void draw() const {
		setfillcolor(ButtonColor);
		bar(r.left, r.top, r.right, r.bottom);
		settextcolor(BLACK);
		drawtext(str.c_str(), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	bool IsPressed(int x, int y) const { return r.PtInRect({ x,y }); }
	string getstr() const { return str; }
	void changepos(int x, int y) {
		r = { x, y, x + ButtonWidth, y + ButtonHeight };
	}
};