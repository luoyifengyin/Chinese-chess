#pragma once
#include "head.h"
#include "Setting.h"

struct Chess {
	IDPlayer player;
	IDChess chess;
};

class Stone {
protected:
	IMAGE Chessimg[29];
	node selected;
public:
	Stone() {
		int i = 0;
		//loadimage(img + 0, "pic\\Board.GIF", Size * 9 + 8, Size * 10 + 7);
		loadimage(Chessimg + i++, "pic\\RK.GIF", Size, Size);
		loadimage(Chessimg + i++, "pic\\RA.GIF", Size, Size);
		loadimage(Chessimg + i++, "pic\\RB.GIF", Size, Size);
		loadimage(Chessimg + i++, "pic\\RN.GIF", Size, Size);
		loadimage(Chessimg + i++, "pic\\RR.GIF", Size, Size);
		loadimage(Chessimg + i++, "pic\\RC.GIF", Size, Size);
		loadimage(Chessimg + i++, "pic\\RP.GIF", Size, Size);
		loadimage(Chessimg + i++, "pic\\BK.GIF", Size, Size);
		loadimage(Chessimg + i++, "pic\\BA.GIF", Size, Size);
		loadimage(Chessimg + i++, "pic\\BB.GIF", Size, Size);
		loadimage(Chessimg + i++, "pic\\BN.GIF", Size, Size);
		loadimage(Chessimg + i++, "pic\\BR.GIF", Size, Size);
		loadimage(Chessimg + i++, "pic\\BC.GIF", Size, Size);
		loadimage(Chessimg + i++, "pic\\BP.GIF", Size, Size);
		/*loadimage(img + 15, "pic\\RKS.GIF", Size, Size);
		loadimage(img + 16, "pic\\RAS.GIF", Size, Size);
		loadimage(img + 17, "pic\\RBS.GIF", Size, Size);
		loadimage(img + 18, "pic\\RNS.GIF", Size, Size);
		loadimage(img + 19, "pic\\RRS.GIF", Size, Size);
		loadimage(img + 20, "pic\\RCS.GIF", Size, Size);
		loadimage(img + 21, "pic\\RPS.GIF", Size, Size);
		loadimage(img + 22, "pic\\BKS.GIF", Size, Size);
		loadimage(img + 23, "pic\\BAS.GIF", Size, Size);
		loadimage(img + 24, "pic\\BBS.GIF", Size, Size);
		loadimage(img + 25, "pic\\BNS.GIF", Size, Size);
		loadimage(img + 26, "pic\\BRS.GIF", Size, Size);
		loadimage(img + 27, "pic\\BCS.GIF", Size, Size);
		loadimage(img + 28, "pic\\BPS.GIF", Size, Size);*/
	}
	virtual bool IsCurplayerChess(int, int) const = 0;
	void setselected(int x, int y) {
		if (0 <= x && x < 10 && 0 <= y && y < 9 && IsCurplayerChess(x, y)) {
			selected.x = x;
			selected.y = y;
		}
		else clearselected();
	}
	void clearselected() { selected = { -1,-1 }; }
	void Kingmove(int, int);
	void Advisormove(int, int);
	void Elephantmove(int, int);
	void Horsemove(int, int);
	void Rookmove(int, int);
	void Cannonmove(int, int);
	void Pawnmove(int, int);
	void paintchess(int x, int y, const Chess& c) const {
		setfillcolor(BLACK);
		solidcircle(Size*x + 4 + Size / 2, Size*y + 3 + Size / 2, Size / 2 - 1);
		putimage(Size*x + 4, Size*y + 3, Chessimg + c.chess + c.player * 7, SRCPAINT);
	}
	virtual bool CheckHaveChess(int, int) const = 0;
	virtual bool IsFlipped() const = 0;
	virtual void move(int, int, short k = 0) = 0;
};
