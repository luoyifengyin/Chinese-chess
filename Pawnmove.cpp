#include "Stone.h"

static cs pawndirx[] = { -1,0,0 },
pawndiry[] = { 0,-1,1 };

void Stone::Pawnmove(int x, int y) {
	bool flag = 1, overriver = 0; short temp;
	if ((Setting::getcurplayer() == IDRED && !IsFlipped()) || (Setting::getcurplayer() == IDBLACK && IsFlipped())) {
		if (selected.x <= 4) overriver = 1;
		temp = 1;
	}
	else {
		if (selected.x >= 5) overriver = 1;
		temp = -1;
	}
	for (int i = 0; i < 3 && flag; i++) {
		if (i > 0 && !overriver) break;
		int xx = selected.x + pawndirx[i] * temp;
		int yy = selected.y + pawndiry[i];
		if (x == xx && y == yy) { flag = 0; move(x, y); }
	}
	if (flag) setselected(x, y);
}