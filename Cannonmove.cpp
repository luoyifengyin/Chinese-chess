#include "Stone.h"

static cs cannondirx[] = { -1,1,0,0 },
cannondiry[] = { 0,0,-1,1 };

void Stone::Cannonmove(int x, int y) {
	bool flag = 1;
	for (int i = 0; i < 4 && flag; i++) {
		bool over = 0;
		int xx = selected.x + cannondirx[i];
		int yy = selected.y + cannondiry[i];
		while (0 <= xx && xx < 10 && 0 <= yy && yy < 9 && flag) {
			if (CheckHaveChess(xx, yy)) {
				if (!over) over = 1;
				else {
					if (x == xx && y == yy) { flag = 0; move(x, y); }
					break;
				}
			}
			else if (!over && x == xx && y == yy) { flag = 0; move(x, y); }
			xx += cannondirx[i];
			yy += cannondiry[i];
		}
	}
	if (flag) setselected(x, y);
}