#include "Wall.h"
#include "../../Collision/Collider/OBBCollider.h"

Wall::Wall(Vector3 startPos, DirectXCommon* dxCommon,std::weak_ptr<CollisionManager> collisionManager, PlayerBase* player,Vector3 length):
	GameObjectBase(dxCommon)
{
	wall = std::make_shared<ObjDraw>(*ObjDraw::Create());
	wall->SetModel(ModelManager::GetIns()->GetModel("Wall"));

	this->player = player;

	// 各軸の向き
	DirectX::XMVECTOR obbNormal[3] = {
		{1.0f,0,0},
		{0,1.0f,0},
		{0,0,1.0f},
	};
	// 各軸の長さ
	float obbLength[3]
	{
		length.x,
		length.y,
		length.z
	};
	// コライダー
	std::shared_ptr<OBBCollider> obb = std::make_shared<OBBCollider>(obbNormal, obbLength);
	wall->SetScale(length);
	obb.get()->SetName("Wall");
	AddCollider(obb, collisionManager);

	pos = startPos;
}

void Wall::Update()
{
	wall->SetPos(pos);

	//画面外（手前）に来たら消去
	if (pos.z < player->GetPos().z - 15) {
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
	//プレイヤーと衝突したら消滅させる
	if (info.hitName == "Player") {
		deleteFlag = true;
	}
}
