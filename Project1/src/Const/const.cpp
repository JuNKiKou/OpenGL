#include "const.h"

MazeOption operator++(MazeOption& _option)
{
	_option = static_cast<MazeOption>((static_cast<int>(_option) + 1) % 5);
	return _option;
}