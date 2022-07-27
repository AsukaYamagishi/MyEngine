#include "Stage.h"

using namespace DirectX;

Stage::Stage()
{
	/*skydome = ModelDraw::Create();
	skydome->SetModel(ModelManager::GetIns()->GetModel(ModelManager::Skydome));
	stage = ModelDraw::Create();
	stage->SetModel(ModelManager::GetIns()->GetModel(ModelManager::Stage));*/
}

Stage::~Stage()
{
}

void Stage::Initialize(DirectXCommon* dxCommon)
{
	this->dxCommon = dxCommon;
}

void Stage::Update()
{
	/*skydome->Update();
	stage->Update();*/
}

void Stage::Draw()
{
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();
	ModelDraw::PreDraw(cmdList);
	/*skydome->Draw();
	stage->Draw();*/
	ModelDraw::PostDraw();
}
