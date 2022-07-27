#include "SphereCollider.h"

void SphereCollider::Update()
{
	DirectX::XMMATRIX matWorld = XMMatrixIdentity();
 	matWorld = XMMatrixTranslation(object->GetPos().x, object->GetPos().y, object->GetPos().z);
	Sphere::centor = matWorld.r[3] + offset;
	Sphere::radius = radius;
}
