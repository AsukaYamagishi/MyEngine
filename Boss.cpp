#include "Boss.h"

using namespace DirectX;

Boss::Boss()
{
	
}

Boss::~Boss()
{


}

void Boss::Initialize(DirectXCommon* dxCommon, KeyboardInput* input, Audio* audio, ModelDraw* player)
{
	// nullptrチェック
	assert(dxCommon);
	assert(input);
	assert(audio);

	this->dxCommon = dxCommon;
	this->input = input;
	this->audio = audio;

}

void Boss::Update()
{
}

void Boss::Draw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

	ModelDraw::PreDraw(cmdList);
	
	ModelDraw::PostDraw();
}

