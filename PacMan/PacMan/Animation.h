#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include <vector>
#include "UGFW.h"
#include "UG_Defines.h"
#include "../EntityState.h"
#include "../MovementDirection.h"

class Animation
{
public:

	void SetCurrentSpriteID(int _spriteID);


protected:
	float fDeltaTime;
	int currentSpriteID;
};

#endif // __ANIMATION_H__
