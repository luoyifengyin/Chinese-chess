#include "Stone.h"

static cs kingdirx[] = { -1,1,0,0 },
kingdiry[] = { 0,0,-1,1 };

void Stone::Kingmove(int x, int y) {
	if ((Setting::getcurplayer() == IDRED && !IsFlipped()) || (Setting::getcurplayer() == IDBLACK && IsFlipped())) {
		if (y < 3 || y > 5 || x < 7) { setselected(x, y); return; }
	}
	else if (y < 3 || y > 5 || x > 2) { setselected(x, y); return; }
	bool flag = 1;
	for (int i = 0; i < 4 && flag; i++) {
		int xx = selected.x + kingdirx[i];
		int yy = selected.y + kingdiry[i];
		if (x == xx && y == yy) {
			flag = 0;
			move(x, y, Setting::getcurplayer() + 1);
		}
	}
	if (flag) setselected(x, y);
}