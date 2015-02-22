#pragma once
class vector2d
{
public:
	vector2d();
	vector2d(float x, float y);
	~vector2d();
	float& x, y;
private:
	float component[2];
};

