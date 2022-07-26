#include "PlayerBase.h"
#include "Camera.h"
#include <time.h>
#include <cassert>
#include "KeyboardInput.h"
#include "ControllerInput.h"

using namespace DirectX;

PlayerBase::PlayerBase(PlayerType type, ModelInput* model)
{
	player = std::make_shared<ModelDraw>(*ModelDraw::Create());
	player->SetModel(ModelManager::GetIns()->GetModel(ModelManager::Player));
}

PlayerBase::~PlayerBase()
{

}

void PlayerBase::Init(DirectXCommon *dxCommon)
{
	// nullptrチェック
	assert(dxCommon);
	this->dxCommon = dxCommon;
	
}

void PlayerBase::Update()
{
	pos = player->GetPos();
	Move();
	player->Update();
}

void PlayerBase::Draw()
{
	player->SetPos(pos);

	ID3D12GraphicsCommandList *cmdList = dxCommon->GetCommandList();

	ModelDraw::PreDraw(cmdList);
	player->Draw();
	ModelDraw::PostDraw();

}

void PlayerBase::Move()
{
	//徐々に止まる
	velocity = velocity * Vector3(0.85f,0.85f,0.85f);
	if (velocity.length() <= 0.01f)
	{
		velocity = { 0,0,0 };
	}

	//キーボード移動
	if (KeyboardInput::GetInstance()->PressKey(DIK_W)) {
		velocity += Vector3(0.0f, move, 0.0f);
	}
	if (KeyboardInput::GetInstance()->PressKey(DIK_S)) {
		velocity += Vector3(0.0f, -move, 0.0f);
	}
	if (KeyboardInput::GetInstance()->PressKey(DIK_A)) {
		velocity += Vector3(-move, 0.0f, 0.0f);
	}
	if (KeyboardInput::GetInstance()->PressKey(DIK_D)) {
		velocity += Vector3(+move, 0.0f, 0.0f);
	}

	//ゲームパッド移動
	////要相談
	if (ControllerInput::GetInstance()->IsPadStick(INPUT_AXIS_LX, 0.1f) != 0 || 
		ControllerInput::GetInstance()->IsPadStick(INPUT_AXIS_LY, 0.1f) != 0)
	{
		velocity.x += move * (ControllerInput::GetInstance()->IsPadStick(INPUT_AXIS_LX, 0.1f) / 500);
		velocity.y += move * -(ControllerInput::GetInstance()->IsPadStick(INPUT_AXIS_LY, 0.1f) / 500);
	}

	//move以上に大きく動かないようにする
	if (velocity.length() > move) {
		velocity = velocity.Normal() * move;
	}

	//フレーム内の移動を適応
	pos += velocity;

	//画面外に出ないようにする
	const float width = 30.0f;
	const float height = 15.0f;
	if (pos.x > width) player->SetPosX(width);
	if (pos.x < -width) player->SetPosX(-width);
	if (player->GetPos().y > height) player->SetPosY(height);
	if (player->GetPos().y < -height) player->SetPosY(-height);

}

void PlayerBase::Attack()
{
}
