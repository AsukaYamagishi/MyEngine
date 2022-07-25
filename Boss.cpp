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
	// nullptr�`�F�b�N
	assert(dxCommon);

	this->dxCommon = dxCommon;
}

void Boss::Update()
{
}

void Boss::Draw()
{
	// �R�}���h���X�g�̎擾
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

	ModelDraw::PreDraw(cmdList);
	
	ModelDraw::PostDraw();
}

