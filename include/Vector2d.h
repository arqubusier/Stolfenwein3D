#ifndef Vector2d_H
#define Vector2d_H
class Vector2d
{
public:
	Vector2d();
	Vector2d(float x, float y);
	~Vector2d();

	friend Vector2d operator+(const Vector2d &v1, const Vector2d &v2);
	friend Vector2d operator-(const Vector2d &v1, const Vector2d &v2);
	Vector2d operator=(const Vector2d &v);


	float& x, y;

private:
	float component[2];
};
#endif
