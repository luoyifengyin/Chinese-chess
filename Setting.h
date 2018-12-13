#pragma once
#include "head.h"
#include "Button.h"
class Setting {
	static IDPlayer curplayer, winner;
	static Button replaybutton;
	static Button surrenderbutton;
public:
	static node move;
	Setting() {
		newmatch();
	}
	static void newmatch() {
		curplayer = IDRED;
		winner = IDNONE;
		clearmove();
	}
	static IDPlayer getcurplayer() { return curplayer; }
	static void changeplayer() { curplayer = (IDPlayer)!curplayer; }
	static IDPlayer getwinner() { return winner; }
	static void win(IDPlayer p) { winner = p; }
	static void clearmove() { move = { -1,-1 }; }
	static bool IsReplayed(int x, int y) { return replaybutton.IsPressed(x, y); }
	static bool IsPressSurrender(int x, int y) { return surrenderbutton.IsPressed(x, y); }
	static void Surrender() {
		win((IDPlayer)!curplayer);
	}
	static void draw(bool flip) {
		if ((curplayer == IDBLACK && !flip) || (curplayer == IDRED && flip)) {
			surrenderbutton.changepos(BoardWidth, 3);
			surrenderbutton.draw();
			if (curplayer == IDBLACK)
				setfillcolor(BLACK);
			else setfillcolor(RED);
			solidcircle(BoardWidth + Size, Size + 6 + Size / 2, Size / 3);
		}
		else {
			surrenderbutton.changepos(BoardWidth, Size * 9 + 3);
			surrenderbutton.draw();
			if (curplayer == IDRED)
				setfillcolor(RED);
			else setfillcolor(BLACK);
			solidcircle(Size * 10, Size * 8 + Size / 2, Size / 3);
		}
		replaybutton.draw();
	}
};