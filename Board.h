#pragma once
#include "Stone.h"
#include "ChessManual.h"
#include <cstring>
#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

class Board : public Stone, public ChessManual {
	Chess MAP[10][9];
	node RK, BK;
	IMAGE Boardimg;
	bool flip;
	const Button flipbutton;
public:
	Board() :flipbutton(BoardWidth, Size * 5, "·­×ª") {
		loadimage(&Boardimg, "pic\\Board.GIF", BoardWidth, BoardHeight);
		initboard();
	}
	void initboard() {
		memset(MAP, -1, sizeof(MAP));
		initchess(IDRED);
		initchess(IDBLACK);
		RK = { 9,4 };
		BK = { 0,4 };
		Setting::newmatch();
		clearselected();
		flip = 0;
		initstep();
	}
	IDChess IsSelected() const {
		if (selected.x == -1) return None;
		else return MAP[selected.x][selected.y].chess;
	}
	bool IsCurplayerChess(int x, int y) const {
		if (0 <= x && x < 10 && 0 <= y && y < 9 && MAP[x][y].player == Setting::getcurplayer()) return true;
		else return false;
	}
	bool IsPressFlip(int x, int y) const { return flipbutton.IsPressed(x, y); }
	void flipboard(bool d = 1) {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 9; j++) {
				swap(MAP[i][j], MAP[9 - i][8 - j]);
			}
		}
		RK = { 9 - RK.x,8 - RK.y };
		BK = { 9 - BK.x,8 - BK.y };
		if (selected.x != -1) selected = { 9 - selected.x,8 - selected.y };
		flip = !flip;
		if (d) draw();
	}
	bool IsFlipped() const { return flip; }
	void printselectedmark(node p) const {
		int dx = p.y*Size + 4, dy = p.x*Size + 3;
		setlinecolor(BLUE);
		setlinestyle(0, 3);
		line(dx, dy, dx + Size / 4, dy);
		line(dx, dy, dx, dy + Size / 4);
		line(dx + Size - 1, dy, dx + Size - 1 - Size / 4, dy);
		line(dx + Size - 1, dy, dx + Size - 1, dy + Size / 4);
		line(dx, dy + Size - 1, dx, dy + Size - 1 - Size / 4);
		line(dx, dy + Size - 1, dx + Size / 4, dy + Size - 1);
		line(dx + Size - 1, dy + Size - 1, dx + Size - 1 - Size / 4, dy + Size - 1);
		line(dx + Size - 1, dy + Size - 1, dx + Size - 1, dy + Size - 1 - Size / 4);
	}
	void draw() const {
		cleardevice();
		putimage(0, 0, &Boardimg);
		setfillcolor(BLACK);
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 9; j++) {
				if (MAP[i][j].chess != None)
					paintchess(j, i, MAP[i][j]);
				//if (MAP[i][j].player == IDRED) {
				//	/*if (selected.x == i && selected.y == j)
				//		putimage(Size*j + 4, Size*i + 3, img + MAP[i][j].chess + 15);
				//	else */putimage(Size*j + 4, Size*i + 3, img + MAP[i][j].chess + 1, SRCPAINT);
				//}
				//else if (MAP[i][j].player == IDBLACK) {
				//	/*if (selected.x == i && selected.y == j)
				//		putimage(Size*j + 4, Size*i + 3, img + MAP[i][j].chess + 22);
				//	else */putimage(Size*j + 4, Size*i + 3, img + MAP[i][j].chess + 8, SRCPAINT);
				//}
			}
		}
		printselectedmark(selected);
		flipbutton.draw();
		ChessManual::draw();
	}
	void takeback();
private:
	void initchess(IDPlayer p) {
		short temp; int i;
		if (p == IDRED) { temp = 1; i = 6; }
		else { temp = -1; i = 3; }
		for (int j = 0; j < 9; j += 2) MAP[i][j] = { p,Pawn };
		i += 1 * temp;
		MAP[i][1] = MAP[i][7] = { p,Cannon };
		i += 2 * temp;
		for (int j = 0; j < 5; j++)
			MAP[i][j] = MAP[i][8 - j] = { p,IDChess(4 - j) };
	}
	bool checkKing(Chess newMAP[10][9]) const {
		int up, down;
		if (RK.y == BK.y) {
			if (!flip) { up = BK.x; down = RK.x; }
			else { up = RK.x; down = BK.x; }
			for (int i = up + 1; i < down; i++) {
				if (newMAP[i][RK.y].chess != None) return false;
			}
			return true;
		}
		return false;
	}
	void move(int x, int y, short k = 0) {
		if (k == 1) RK = { x,y };
		else if (k == 2) BK = { x,y };
		Chess newMAP[10][9];
		memcpy(newMAP, MAP, sizeof(MAP));
		newMAP[x][y] = newMAP[selected.x][selected.y];
		newMAP[selected.x][selected.y] = { IDNONE,None };
		if (checkKing(newMAP)) {
			if (k == 1) RK = { selected.x,selected.y };
			else if (k == 2) BK = { selected.x,selected.y };
			return;
		}
		step m = { selected.x,selected.y,x,y };
		if (MAP[x][y].chess != None) m.eat = { MAP[x][y].player,MAP[x][y].chess };
		else m.eat = { IDNONE,None };
		m.flip = flip;
		memcpy(MAP, newMAP, sizeof(MAP));
		movestep.push(m);
		Setting::changeplayer();
		Setting::move = { x,y };
		PlaySound("sound\\sound.wav", NULL, SND_FILENAME | SND_ASYNC);
		if (m.eat.chess == King) {
			Setting::win(Setting::getcurplayer());
		}
	}
	bool CheckHaveChess(int x, int y) const {
		if (MAP[x][y].chess != None) return true;
		else return false;
	}
};

void Board::takeback() {
	if (movestep.empty()) return;
	step m = movestep.top(); movestep.pop();
	bool flag = 0;
	if (m.flip != flip) { flipboard(0); flag = 1; }
	MAP[m.startx][m.starty] = MAP[m.endx][m.endy];
	MAP[m.endx][m.endy] = m.eat;
	Setting::changeplayer();
	if (flag) flipboard(0);
	clearselected();
	draw();
}