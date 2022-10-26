#include "Wall.h"
#include "../../Collision/Collider/OBBCollider.h"

Wall::Wall(Vector3 startPos, DirectXCommon* dxCommon,std::weak_ptr<CollisionManager> collisionManager, PlayerBase* player,Vector3 length):
	GameObjectBase(dxCommon)
{
	wall = std::make_shared<ObjDraw>(*ObjDraw::Create());
	wall->SetModel(ModelManager::GetIns()->GetModel(ModelManager::WALL));

	this->player = player;

	// �e���̌���
	DirectX::XMVECTOR obbNormal[3] = {
		{1.0f,0,0},
		{0,1.0f,0},
		{0,0,1.0f},
	};
	// �e���̒���
	float obbLength[3]
	{
		length.x,
		length.y,
		length.z
	};
	// �R���C�_�[
	std::shared_ptr<OBBCollider> obb = std::make_shared<OBBCollider>(obbNormal, obbLength);
	wall->SetScale(length);
	obb.get()->SetName("Wall");
	AddCollider(obb, collisionManager);

	pos = startPos;
}

void Wall::Update()
{
	wall->SetPos(pos);

	//��ʊO�i��O�j�ɗ��������
	if (pos.z < player->GetPos().z - 30) {
		deleteFlag = true;
	}
}

void Wall::Draw()
{
	wall->Update();
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();
	ObjDraw::PreDraw(cmdList);
	wall->Draw();
	ObjDraw::PostDraw();
}

void Wall::OnCollision(CollisionInfo info)
{
	//�v���C���[�ƏՓ˂�������ł�����
	if (info.hitName == "Player") {
		deleteFlag = true;
	}
}
