#pragma once
#include "CollisionPrimitive.h"
#include "BaseCollider.h"
class SphereCollider :
    public BaseCollider,public Sphere
{
public:
    SphereCollider(std::string name = "", DirectX::XMVECTOR offset = { 0,0,0,0 }, float radius = 1.0f):
    offset(offset),
    radius(radius)
    {
        shapeType = CollisionShapeType::SHAPE_SPHERE;
        this->collisionName = name;
        
    }

    void Update() override;




private:
    DirectX::XMVECTOR offset = {0,0,0,0};
    float radius = 1.0f;
};

