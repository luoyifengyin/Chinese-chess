#include "Stone.h"

static cs elephantdirx[] = { -2,2,-2,2 },
elephantdiry[] = { -2,-2,2,2 },

elephantcheckx[] = { -1,1,-1,1 },
elephantchecky[] = { -1,-1,1,1 };

void Stone::Elephantmove(int x, int y) {
	if ((Setting::getcurplayer() == IDRED && !IsFlipped()) || (Setting::getcurplayer() == IDBLACK && IsFlipped())) {
		if (x < 5) { setselected(x, y); return; }
	}
	else if (x > 4) { setselected(x, y); return; }
	bool flag = 1;
	for (int i = 0; i < 4; i++) {
		int xx = selected.x + elephantdirx[i];
		int yy = selected.y + elephantdiry[i];
		int checkdirx = selected.x + elephantcheckx[i];
		int checkdiry = selected.y + elephantchecky[i];
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