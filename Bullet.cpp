#include "Bullet.h"

Bullet::Bullet(DirectXCommon* dxCommon, Vector3 pos, Vector3 velosity)
{
	model = ModelDraw::Create();
	model->SetModel(ModelManager::GetIns()->GetModel(ModelManager::sphere));
	model->SetPos(pos);
	move = velosity;

	this->dxCommon = dxCommon;
}

void Bullet::Update()
{
	move += Vector3{ 0, -0.3, 0 };

	float f = 0.1f * move.Length();
	move += -move.Normal() * f;

 	model->SetPos(model->GetPos() + move);
}

void Bullet::Draw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

	ModelDraw::PreDraw(cmdList);
	model->Draw();
	ModelDraw::PostDraw();
}
