// Collider.h

#ifndef COLLIDER_H_INCLUDED
#define COLLIDER_H_INCLUDED

class Entity;

class Collider
{
public:
	Collider(int x, int y);

	bool HasParent();
	void SetParent(Entity* parent);
	Entity* GetParent();

	void SetPosition(int x, int y);
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
