#include "Wall.h"
#include "OBBCollider.h"

Wall::Wall(Vector3 startPos, DirectXCommon* dxCommon, std::shared_ptr<GameObjectManager> gameObjManager, std::shared_ptr<CollisionManager> collisionManager, PlayerBase* player):
	GameObject(dxCommon)
{
	wall = std::make_shared<ModelDraw>(*ModelDraw::Create());
	wall->SetModel(ModelManager::GetIns()->GetModel(ModelManager::WALL));

	this->player = player;

	// 各軸の向き
	DirectX::XMVECTOR obbNormal[3] = {
		{1.0f,0,0},
		{0,1.0f,0},
		{0,0,1.0f},
	};
	// 各軸の長さ
	float obbLength[3] = {
		rand() % 10 + 1,
		rand() % 10 + 1,
		1.0f
	};
	// コライダー
	std::shared_ptr<OBBCollider> obb = std::make_shared<OBBCollider>(obbNormal, obbLength);
	wall->SetScale(Vector3(obbLength[0], obbLength[1], obbLength[2]));
	obb.get()->SetName("Wall");
	AddCollider(obb, collisionManager);

	pos = startPos;
}

void Wall::Update()
{
	wall->SetPos(pos);
	if (pos.z < player->GetPos().z - 30) {
		deleteFlag = true;
	}
}

void Wall::Draw()
{
	wall->Update();
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();
	ModelDraw::PreDraw(cmdList);
	wall->Draw();
	ModelDraw::PostDraw();
}

void Wall::OnCollision(CollisionInfo info)
{
	if (info.hitName == "Player") {
		deleteFlag = true;

	}
}
