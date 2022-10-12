#pragma once
#include <string>
#include "../CollisionInfo.h"
#include "../../GameObject/GameObjectBase.h"

//Collition用形状(bit演算で衝突タイプを算出)
enum class CollisionShapeType {
	SHAPE_UNKONOWN = -1, //形状設定なし

	SHAPE_SPHERE	= 0x00001,	//球
	SHAPE_OBB		= 0x00002,  //OBB 

};

class BaseCollider
{
public:
	friend class CollisionManager;
	BaseCollider() = default;
	virtual ~BaseCollider() = default;

	virtual void Update() = 0;

#pragma region 関数
	/// <summary>
	/// 形状タイプ情報取得
	/// </summary>
	/// <returns>形状タイプ</returns>
	inline CollisionShapeType GetShapeType() { return shapeType;}

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	std::string GetCollisionName() { return collisionName; }

	/// <summary>
	/// 
	/// </summary>
	/// <param name="info"></param>
	inline void OnCollision(CollisionInfo info) {
		this->object->OnCollision(info);
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="object"></param>
	inline void SetObject(GameObjectBase* object) { this->object = object; }

	/// <summary>
	/// 
	/// </summary>
	/// <param name="name"></param>
	inline void SetName(const std::string name) { this->collisionName = name; }
#pragma endregion

protected:
	//オブジェクトのポインタ
	GameObjectBase* object = nullptr;
	//形状タイプ(初期設定では不明形となる)
	CollisionShapeType shapeType = CollisionShapeType::SHAPE_UNKONOWN;
	//
	std::string collisionName;

};

