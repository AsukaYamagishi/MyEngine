#pragma once
#include "CollisionPrimitive.h"
#include "Code/Collision/Collider/BaseCollider.h"
class SphereCollider :
    public BaseCollider,public Sphere
{
public:
    SphereCollider(std::string name = "", DirectX::XMVECTOR offset = { 0,0,0,0 }, float radius = 1.0f):
    offset(offset)
    {
        shapeType = CollisionShapeType::SHAPE_SPHERE;
        this->radius = radius;
        this->collisionName = name;

        
    }

    void Update() override;

    void SetRadius(float radius) { this->radius = radius; }
    void SetOffset(DirectX::XMVECTOR offset) { this->offset = offset; }

private:
    DirectX::XMVECTOR offset = {0,0,0,0};
};

