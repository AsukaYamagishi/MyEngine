#include "Player.h"
#include "Camera.h"
#include <time.h>
#include <cassert>
#include "KeyboardInput.h"

using namespace DirectX;

Player::Player()
{
	player = ModelDraw::Create();
	player->SetModel(ModelManager::GetIns()->GetModel(ModelManager::Player));
}

Player::~Player()
{


}

void Player::Init(DirectXCommon *dxCommon)
{
	// nullptrチェック
	assert(dxCommon);
	this->dxCommon = dxCommon;
	
	player->SetScale(Vector3(1, 1, 1));
	player->SetPos(Vector3(0, 5, 0));
}

void Player::Update()
{
	player->Update();
	Move();
}

void Player::Draw()
{
	ID3D12GraphicsCommandList *cmdList = dxCommon->GetCommandList();

	ModelDraw::PreDraw(cmdList);
	player->Draw();
	ModelDraw::PostDraw();

}

void Player::Move()
{
	if (KeyboardInput::GetInstance()->PressKey(DIK_W)) {
		player->SetPos(player->GetPos() + Vector3(0.0f, 0.0f, move));
	}
	if (KeyboardInput::GetInstance()->PressKey(DIK_S)) {
		player->SetPos(player->GetPos() + Vector3(0.0f, 0.0f, -move));
	}
	if (KeyboardInput::GetInstance()->PressKey(DIK_A)) {
		player->SetPos(player->GetPos() + Vector3(-move, 0.0f, 0.0f));
	}
	if (KeyboardInput::GetInstance()->PressKey(DIK_D)) {
		player->SetPos(player->GetPos() + Vector3(+move, 0.0f, 0.0f));
	}
	
	player->Update();
}
