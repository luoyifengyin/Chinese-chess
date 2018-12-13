#include "Stone.h"

static cs horsedirx[] = { -1,1,-2,2,-2,2,-1,1 },
horsediry[] = { -2,-2,-1,-1,1,1,2,2 },

horsecheckx[] = { 0,0,-1,1,-1,1,0,0 },
horsechecky[] = { -1,-1,0,0,0,0,1,1 };

void Stone::Horsemove(int x, int y) {
	bool flag = 1;
	for (int i = 0; i < 8; i++) {
		int xx = selected.x + horsedirx[i];
		int yy = selected.y + horsediry[i];
		int checkdirx = selected.x + horsecheckx[i];
		int checkdiry = selected.y + horsechecky[i];
		if (x == xx && y == yy) {
			if (!CheckHaveChess(checkdirx, checkdiry)) {
				move(x, y);
				flag = 0;
			}
			break;
		}
	}
	if (flag) setselected(x, y);
}