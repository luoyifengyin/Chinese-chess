#pragma once
#include <algorithm>
#include <afxwin.h>
#include <graphics.h>
using namespace std;
typedef const short cs;
const int Size = 41;
#define BoardWidth (Size * 9 + 8)
#define BoardHeight (Size * 10 + 7)
#define ButtonWidth (Size * 2)
#define ButtonHeight (Size)
#define ScreenWidth ((BoardWidth) + (ButtonWidth))
#define ScreenHeight (BoardHeight)

enum IDPlayer{
	IDNONE = -1,
	IDRED,
	IDBLACK
};

enum IDChess {
	None = -1,
	King,
	Advisor,
	Elephant,
	Horse,
	Rook,
	Cannon,
	Pawn
};

struct node {
	int x, y;
};