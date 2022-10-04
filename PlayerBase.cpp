#include "PlayerBase.h"
#include "Camera.h"
#include <time.h>
#include <cassert>
#include "KeyboardInput.h"
#include "ControllerInput.h"
#include "Code/GameObject/Player/PlayerBullet.h"
#include "SphereCollider.h"
#include "OBBCollider.h"


using namespace DirectX;

PlayerBase::PlayerBase(DirectXCommon* dxCommon, std::shared_ptr<CollisionManager> collisionManager, PlayerType type):
	GameObject(dxCommon)
{
	player = std::make_shared<ModelDraw>(*ModelDraw::Create());
	player->SetModel(ModelManager::GetIns()->GetModel(ModelManager::PLAYER));
	this->collisionManager = collisionManager;

	std::shared_ptr<SphereCollider> sphere = std::make_shared<SphereCollider>();
	sphere.get()->SetName("Player");
	AddCollider(sphere, collisionManager);
}

PlayerBase::~PlayerBase()
{

}

void PlayerBase::Init()
{
	
	
}

void PlayerBase::Update()
{
	pos = player->GetPos();

	Attack();

	Move();
}

void PlayerBase::Draw()
{
	player->Update();
	player->SetPos(pos);

	ID3D12GraphicsCommandList *cmdList = dxCommon->GetCommandList();

	ModelDraw::PreDraw(cmdList);
	player->Draw();
	ModelDraw::PostDraw();

}

void PlayerBase::OnCollision(CollisionInfo info)
{
	
	if (info.hitName == "Wall") {
		flontMove = -4.0f;

	}
}

void PlayerBase::Move()
{
	if (flontMove < 0.2f) {
		flontMove += 0.1f;
	}
	else {
		flontMove = 0.2f;
	}
	//徐々に止まる
	velocity = velocity * Vector3(0.85f, 0.85f, 0.85f);
	velocity.z = flontMove;
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
	if (pos.x > width){
		pos.x = width;
		velocity = { 0,0,0 };
	}
	if (pos.x < -width){
		pos.x = -width;
		velocity = { 0,0,0 };
	}
	if (pos.y > height) {
		pos.y = height;
		velocity = { 0,0,0 };
	}
	if (pos.y < -height){
		pos.y = -height;
		velocity = { 0,0,0 };
	}

}

void PlayerBase::Attack()
{
	if (KeyboardInput::GetInstance()->PressKeyTrigger(DIK_SPACE))
	{
		GameObject::Create<Bullet>(dxCommon, collisionManager, pos + Vector3{ 0,0,1.0f }, Vector3{ 0.0f,0.0f,0.7f });
	}
}
