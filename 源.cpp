#include "Board.h"
#include <conio.h>
#include <string>
Board b;

void init() {
	initgraph(ScreenWidth, ScreenHeight);
	setbkmode(TRANSPARENT);
	setbkcolor(GREEN);
	BeginBatchDraw();
}

void drawscreen() {
	cleardevice();
	b.draw();
	if (Setting::move.x != -1) b.printselectedmark(Setting::move);
	Setting::draw(b.IsFlipped());
	FlushBatchDraw();
}

int Gameover() {
	int reply;
	if (Setting::getwinner() == IDRED)
		reply = MessageBox(0, "是否重新开始游戏？", "红方胜利！", MB_YESNO | MB_SYSTEMMODAL);
	else reply = MessageBox(0, "是否重新开始游戏？", "黑方胜利！", MB_YESNO | MB_SYSTEMMODAL);
	return reply;
}

bool Start() {
	b.initboard();
	drawscreen();
	while (Setting::getwinner() == IDNONE) {
		Setting::clearmove();
		MOUSEMSG msg;
		msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN) {
			if (msg.x < Size * 9 + 8) {
				int y = (msg.x - 8) / Size;
				int x = (msg.y - 7) / Size;
				if (b.IsSelected() == None || b.IsCurplayerChess(x, y))
					b.setselected(x, y);
				else if (b.IsSelected() == King)
					b.Kingmove(x, y);
				else if (b.IsSelected() == Advisor)
					b.Advisormove(x, y);
				else if (b.IsSelected() == Elephant)
					b.Elephantmove(x, y);
				else if (b.IsSelected() == Horse)
					b.Horsemove(x, y);
				else if (b.IsSelected() == Rook)
					b.Rookmove(x, y);
				else if (b.IsSelected() == Cannon)
					b.Cannonmove(x, y);
				else if (b.IsSelected() == Pawn)
					b.Pawnmove(x, y);
			}
			else {
				if (Setting::IsPressSurrender(msg.x, msg.y))
					Setting::Surrender();
				else if (b.ChessManual::IsPressed(msg.x, msg.y))
					b.takeback();
				else if (b.IsPressFlip(msg.x, msg.y))
					b.flipboard();
				else if (Setting::IsReplayed(msg.x, msg.y)) return true;
			}
			drawscreen();
		}
	}
	if (Gameover() == IDYES) return true;
	else return false;
}

int main() {
	init();
	while (Start());
	EndBatchDraw();
	closegraph();
	return 0;
}
