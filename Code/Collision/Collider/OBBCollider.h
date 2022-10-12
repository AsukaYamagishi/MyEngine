#pragma once
#include "BaseCollider.h"
#include "../CollisionPrimitive.h"

class OBBCollider :
    public BaseCollider , public OBB
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="normalDirect">�����x�N�g��</param>
    /// <param name="length">����</param>
    /// <param name="name"></param>
    /// <param name="offset"></param>
    OBBCollider(DirectX::XMVECTOR normalDirect[3], float length[3], std::string name = "", DirectX::XMVECTOR offset = { 0,0,0,0 }) :
        offset(offset)
    {
        //OBB������������t�^
        shapeType = CollisionShapeType::SHAPE_OBB;

        //�e���̒������Z�b�g
        this->length[0] = length[0];
        this->length[1] = length[1];
        this->length[2] = length[2];

        //�e���̕����x�N�g�����Z�b�g
        this->normalDirect[0] = normalDirect[0];
        this->normalDirect[1] = normalDirect[1];
        this->normalDirect[2] = normalDirect[2];

    }

    void Update() override;

    void SetOffset(DirectX::XMVECTOR offset) { this->offset = offset; }

private:
    DirectX::XMVECTOR offset = { 0,0,0,0 };
};

