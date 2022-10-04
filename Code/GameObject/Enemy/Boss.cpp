#include "Boss.h"

using namespace DirectX;

Boss::Boss()
{
	
}

Boss::~Boss()
{


}

void Boss::Init(DirectXCommon* dxCommon)
{
	// nullptrチェック
	assert(dxCommon);

	this->dxCommon = dxCommon;
}

void Boss::Update()
{
}

void Boss::Draw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

	ObjDraw::PreDraw(cmdList);
	
	ObjDraw::PostDraw();
}

