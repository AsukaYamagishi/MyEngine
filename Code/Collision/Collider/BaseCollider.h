#pragma once
#include "../../GameObject/GameObjectBase.h"
#include "../CollisionInfo.h"
#include <string>

enum class CollisionShapeType {
	SHAPE_UNKONOWN = -1,

	SHAPE_SPHERE	= 0x00001,	//球
	SHAPE_OBB		= 0x00002 

};

class BaseCollider
{
public:
	friend class CollisionManager;
	BaseCollider() = default;
	virtual ~BaseCollider() = default;

	virtual void Update() = 0;

	inline CollisionShapeType GetShapeType() { return shapeType;}
	std::string GetCollisionName() { return collisionName; }

	inline void OnCollision(CollisionInfo info) {
		this->object->OnCollision(info);
	}
	inline void SetObject(GameObjectBase* object) { this->object = object; }
	inline void SetName(const std::string name) { this->collisionName = name; }

protected:
	//オブジェクトのポインタ
	GameObjectBase* object = nullptr;
	//形状タイプ
	CollisionShapeType shapeType = CollisionShapeType::SHAPE_UNKONOWN;
	std::string collisionName;

};

