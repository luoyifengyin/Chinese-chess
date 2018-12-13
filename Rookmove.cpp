#include "Stone.h"

static cs rookdirx[] = { -1,1,0,0 },
rookdiry[] = { 0,0,-1,1 };

void Stone::Rookmove(int x, int y) {
	bool flag = 1;
	for (int i = 0; i < 4 && flag; i++) {
		int xx = selected.x + rookdirx[i];
		int yy = selected.y + rookdiry[i];
		while (0 <= xx && xx < 10 && 0 <= yy && yy < 9 && flag && !IsCurplayerChess(xx, yy)) {
			if (x == xx && y == yy) { flag = 0; move(x, y); }
			if (CheckHaveChess(xx, yy)) break;
			xx += rookdirx[i];
			yy += rookdiry[i];
		}
	}
	if (flag) setselected(x, y);
}