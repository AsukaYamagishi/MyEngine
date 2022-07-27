#pragma once
#include <string>
#include <DirectXMath.h>

class GameObject;
class BaseCollider;
class CollisionInfo
{
public:
	CollisionInfo(GameObject* obj = nullptr, std::string myNane = "")
	{
		this->object = obj;
		this->hitName = hitName;
	}

	GameObject* object = nullptr;

	std::string hitName;
};

