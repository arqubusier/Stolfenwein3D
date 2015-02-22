#ifndef Vector2d_H
#define Vector2d_H
class Vector2d
{
public:
	Vector2d();
	Vector2d(float x, float y);
	~Vector2d();
	float& x, y;
private:
	float component[2];
};
#endif
