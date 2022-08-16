#include "OBBCollider.h"

void OBBCollider::Update()
{
	DirectX::XMMATRIX matWorld = XMMatrixIdentity();
	matWorld = XMMatrixTranslation(object->GetPos().x, object->GetPos().y, object->GetPos().z);
	OBB::centor = matWorld.r[3] + offset;
    this->length[0] = length[0];
    this->length[1] = length[1];
    this->length[2] = length[2];

    this->normalDirect[0] = normalDirect[0];
    this->normalDirect[1] = normalDirect[1];
    this->normalDirect[2] = normalDirect[2];
}
