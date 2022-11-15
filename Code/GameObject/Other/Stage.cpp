#include "Stage.h"

using namespace DirectX;

Stage::Stage(DirectXCommon* dxCommon, PlayerBase* player):
	GameObjectBase(dxCommon)
{
	this->dxCommon = dxCommon;
	playerData = player;
	
	skydome = std::make_shared<ObjDraw>(*ObjDraw::Create());
	skydome->SetModel(ModelManager::GetIns()->GetModel(ModelManager::SKYDOME));
	skydome->SetPos(playerData->GetPos());
	/*stage = ModelDraw::Create();
	stage->SetModel(ModelManager::GetIns()->GetModel(ModelManager::Stage));*/
}

Stage::~Stage()
{
}

void Stage::Init()
{
	
}

void Stage::Update()
{
	pos.z = playerData->GetPos().z;
}

void Stage::Draw()
{
	skydome->Update();
	skydome->SetPos(pos);

	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();
	ObjDraw::PreDraw(cmdList);
	skydome->Draw();
	//stage->Draw();
	ObjDraw::PostDraw();
}
