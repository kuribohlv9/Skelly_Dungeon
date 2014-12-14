// CollisionManager.h

#ifndef COLLISIONMANAGER_H_INCLUDED
#define COLLISIONMANAGER_H_INCLUDED

class Collider;

class CollisionManager
{
public:
	// note(tommi): this method below is a special one
	//   since it is static it belongs to the class
	//   and not an instance of a class
	//
	// we can access static methods by doing ClassName::StaticMethod(...)
	//   i.e we do not need an instance to access this method
	// it follows the same principles with 'belongs to' or ::)
	// 
	// we can also have static member variables
	//   same thing applies to the as to methods
	// they belong to the class, and not a specific instance of the class
	// all instances can access it

	static bool Check(Collider* lhs, Collider* rhs, int& overlapX, int& overlapY);
};

#endif // COLLISIONMANAGER_H_INCLUDED
