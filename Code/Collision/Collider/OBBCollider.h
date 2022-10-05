#pragma once
#include "../CollisionPrimitive.h"
#include "BaseCollider.h"
class OBBCollider :
    public BaseCollider , public OBB
{
public:
    OBBCollider(DirectX::XMVECTOR normalDirect[3], float length[3], std::string name = "", DirectX::XMVECTOR offset = { 0,0,0,0 }) :
        offset(offset)
    {
        shapeType = CollisionShapeType::SHAPE_OBB;
        this->length[0] = length[0];
        this->length[1] = length[1];
        this->length[2] = length[2];

        this->normalDirect[0] = normalDirect[0];
        this->normalDirect[1] = normalDirect[1];
        this->normalDirect[2] = normalDirect[2];

    }

    void Update() override;

    void SetOffset(DirectX::XMVECTOR offset) { this->offset = offset; }

private:
    DirectX::XMVECTOR offset = { 0,0,0,0 };
};

