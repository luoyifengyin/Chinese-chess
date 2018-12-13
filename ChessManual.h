#pragma once
#include "Stone.h"
#include "Button.h"
#include <stack>

struct step {
	int startx, starty;
	int endx, endy;
	Chess eat;
	bool flip;
};

class ChessManual : public Button {
protected:
	stack<step> movestep;
	//const Button button;
	void initstep() { while (!movestep.empty()) movestep.pop(); }
public:
	ChessManual(int x = BoardWidth, int y = Size * 3) : Button(x, y, "»ÚÆå") {
		initstep();
	}
	virtual void takeback() = 0;
};
