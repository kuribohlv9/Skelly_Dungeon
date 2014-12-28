// Collider.h

#ifndef COLLIDER_H_INCLUDED
#define COLLIDER_H_INCLUDED

class Entity;

class Collider
{
public:
	Collider(float x, float y);

	bool HasParent();
	void SetParent(Entity* parent);
	Entity* GetParent();

	void SetPosition(float x, float y);
	void SetWidthHeight(int width, int height);

	int GetX();
	int GetY();
	int GetWidth();
	int GetHeight();

	void Refresh();

private:
	Entity* m_parent;
	SDL_Rect m_area;
};

#endif // COLLIDER_H_INCLUDED
