#include "Stone.h"

static cs advisordirx[] = { -1,1,-1,1 },
advisordiry[] = { -1,-1,1,1 };

void Stone::Advisormove(int x, int y) {
	if ((Setting::getcurplayer() == IDRED && !IsFlipped()) || (Setting::getcurplayer() == IDBLACK && IsFlipped())) {
		if (y < 3 || y > 5 || x < 7) { setselected(x, y); return; }
	}
	else if (y < 3 || y > 5 || x > 2) { setselected(x, y); return; }
	bool flag = 1;
	for (int i = 0; i < 4 && flag; i++) {
		int xx = selected.x + advisordirx[i];
		int yy = selected.y + advisordiry[i];
		if (x == xx && y == yy) { flag = 0; move(x, y); }
	}
	if (flag) setselected(x, y);
}