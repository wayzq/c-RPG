#pragma once
class CVec2
{
public:
	CVec2()
	{
		x = 0;
		y = 0;
		xBk = 0;
		yBk = 0;
	}
	CVec2(int x, int y);
	int x;
	int y;
	int xBk;
	int yBk;
};

