#include "PlayerBase.h"
#include "PlayerBullet.h"
#include <time.h>
#include <cassert>
#include "../../Camera/Camera.h"
#include "../../Input/KeyboardInput.h"
#include "../../Input/ControllerInput.h"
#include "../../Collision/Collider/SphereCollider.h"
#include "../../Collision/Collider/OBBCollider.h"


using namespace DirectX;

PlayerBase::PlayerBase(DirectXCommon* dxCommon, std::shared_ptr<CollisionManager> collisionManager, PlayerType type):
	GameObjectBase(dxCommon)
{
	player = std::make_shared<ObjDraw>(*ObjDraw::Create());
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

	ObjDraw::PreDraw(cmdList);
	player->Draw();
	ObjDraw::PostDraw();

}

void PlayerBase::OnCollision(CollisionInfo info)
{
	
	if (info.hitName == "Wall") {
		flontMove = -4.0f;

	}
}

void PlayerBase::Move()
{
	if (flontMove < 0.3f) {
		flontMove += 0.1f;
	}
	else {
		flontMove = 0.3f;
	}
	//徐々に止まる
	velocity = velocity * Vector3(0.85f, 0.85f, 0.85f);
	velocity.z = flontMove;
	if (velocity.Length() <= 0.01f)
	{
		velocity = { 0,0,0 };
	}

	//キーボード移動
	if (KeyboardInput::GetIns()->PressKey(DIK_W) 
		|| KeyboardInput::GetIns()->PressKey(DIK_UP)) {
		velocity += Vector3(0.0f, move, 0.0f);
	}
	if (KeyboardInput::GetIns()->PressKey(DIK_S)
		|| KeyboardInput::GetIns()->PressKey(DIK_DOWN)) {
		velocity += Vector3(0.0f, -move, 0.0f);
	}
	if (KeyboardInput::GetIns()->PressKey(DIK_A)
		|| KeyboardInput::GetIns()->PressKey(DIK_LEFT)) {
		velocity += Vector3(-move, 0.0f, 0.0f);
	}
	if (KeyboardInput::GetIns()->PressKey(DIK_D)
		|| KeyboardInput::GetIns()->PressKey(DIK_RIGHT)) {
		velocity += Vector3(+move, 0.0f, 0.0f);
	}


	//ゲームパッド移動
	if (ControllerInput::GetIns()->IsPadStick(INPUT_AXIS_LX, 0.1f) != 0 ||
		ControllerInput::GetIns()->IsPadStick(INPUT_AXIS_LY, 0.1f) != 0)
	{
		velocity.x += move * (ControllerInput::GetIns()->IsPadStick(INPUT_AXIS_LX, 0.1f) / 500.0f);
		velocity.y += move * -(ControllerInput::GetIns()->IsPadStick(INPUT_AXIS_LY, 0.1f) / 500.0f);
	}

	//move以上に大きく動かないようにする
	if (velocity.Length() > move) {
		velocity = velocity.Normalized() * move;
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
	//スペースorBを押すと弾が飛ぶ(長距離攻撃挙動)
	if (KeyboardInput::GetIns()->PressKeyTrigger(DIK_SPACE)
		|| ControllerInput::GetIns()->IsPadButtonTrigger(XBOX_INPUT_B))
	{
		GameObjectBase::Create<Bullet>(dxCommon, collisionManager, pos + Vector3{ 0,0,1.0f }, Vector3{ 0.0f,0.0f,0.7f });
	}
}
