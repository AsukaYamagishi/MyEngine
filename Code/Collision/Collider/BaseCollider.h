#pragma once
#include <string>
#include "../CollisionInfo.h"
#include "../../GameObject/GameObjectBase.h"

//Collition�p�`��(bit���Z�ŏՓ˃^�C�v���Z�o)
enum class CollisionShapeType {
	SHAPE_UNKONOWN = -1, //�`��ݒ�Ȃ�

	SHAPE_SPHERE	= 0x00001,	//��
	SHAPE_OBB		= 0x00002,  //OBB 

};

class BaseCollider
{
public:
	friend class CollisionManager;
	BaseCollider() = default;
	virtual ~BaseCollider() = default;

	virtual void Update() = 0;

#pragma region �֐�
	/// <summary>
	/// �`��^�C�v���擾
	/// </summary>
	/// <returns>�`��^�C�v</returns>
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
	//�I�u�W�F�N�g�̃|�C���^
	GameObjectBase* object = nullptr;
	//�`��^�C�v
	CollisionShapeType shapeType = CollisionShapeType::SHAPE_UNKONOWN;
	//
	std::string collisionName;

};

