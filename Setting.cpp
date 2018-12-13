#include "Setting.h"
static const int x = BoardWidth;
IDPlayer Setting::curplayer, Setting::winner;
node Setting::move;
Button Setting::replaybutton(x, Size * 7, "÷ÿ¿¥");
Button Setting::surrenderbutton(x, Size * 9 + 3, "Õ∂Ωµ");