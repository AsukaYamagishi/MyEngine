#pragma once
#include <string>
#include <DirectXMath.h>

class GameObjectBase;
class BaseCollider;
class CollisionInfo
{
public:
	CollisionInfo(GameObjectBase* obj = nullptr, std::string myNane = "")
	{
		this->object = obj;
		this->hitName = hitName;
	}

	GameObjectBase* object = nullptr;

	std::string hitName;
};

