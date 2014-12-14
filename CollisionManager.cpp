// CollisionManager.cpp

#include "stdafx.h"
#include "Collider.h"
#include "CollisionManager.h"

bool CollisionManager::Check(Collider* lhs, Collider* rhs, int& overlapX, int& overlapY)
{
	// we use something called Separating Axis Theorem
	//   link: en.wikipedia.org/wiki/Hyperplane_separation_theorem#Use_in_collision_detection

	// we use SAT to check if two axis aligned boxes (the shape can basically be any polygon
	// with SAT) are overlapping, and we check one axis at a time: 
	// if one axis does not overlap (i e separates) we have no collision
	//
	//               .> ,-------------.
	//               |  |             |
	//   halfHeightA |  |             |
	//               |  |      A      |                              <.
	//               `> |           ,---------.  <.                   |
	//                  |           |         |   | halfHeightB       |  deltaCenterY
	//                  `-----------|    B    |  <´                  <´
	//                              |         |
  //                              `---------´
	//                  ^------^         ^----^
	//                  halfWidthA       halfWidthB
	//
	//                         ^---------^
	//                         deltaCenterX
	//
	//  if deltaCenterX < (halfWidthA + halfWidthB)
	//     if deltaCenterY < (halfHeightA + halfHeightB)
	//       handle collision
	//     endif
	//  endif
	// 


	overlapX = 0;
	overlapY = 0;

	// find center of colliders
	int lhsHalfWidth = lhs->GetWidth() / 2;
	int rhsHalfWidth = rhs->GetWidth() / 2;
	int lhsCenterX = lhs->GetX() + lhsHalfWidth;
	int rhsCenterX = rhs->GetX() + rhsHalfWidth;
	int centerDeltaX = lhsCenterX - rhsCenterX;

	// first we check if the overlap in the x-axis
	int halfWidth = (lhsHalfWidth + rhsHalfWidth);
	if (abs(centerDeltaX) < halfWidth)
	{
		int lhsHalfHeight = lhs->GetHeight() / 2;
		int rhsHalfHeight = rhs->GetHeight() / 2;
		int lhsCenterY = lhs->GetY() + lhsHalfHeight;
		int rhsCenterY = rhs->GetY() + rhsHalfHeight;
		int centerDeltaY = lhsCenterY - rhsCenterY;

		// then check for overlap in y-axis
		int halfHeight = (lhsHalfHeight + rhsHalfHeight);
		if (abs(centerDeltaY) < halfHeight)
		{
			int deltaX = halfWidth - abs(centerDeltaX);
			int deltaY = halfHeight - abs(centerDeltaY);

			// now we find the smallest of the two overlap in axis
			if (deltaY < deltaX)
			{
				overlapY = deltaY;
				if (centerDeltaY < 0)
					overlapY = -overlapY;
			}
			else if (deltaY > deltaX)
			{
				overlapX = deltaX;
				if (centerDeltaX < 0)
					overlapX = -overlapX;
			}
			else
			{
				if (centerDeltaX < 0)
					overlapX = -deltaX;
				else 
					overlapX = deltaX;

				
				if (centerDeltaY < 0)
					overlapY = -deltaY;
				else
					overlapY = deltaY;

			}
			return true;
		}
	}

	return false;
}
