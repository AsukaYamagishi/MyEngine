#include "PlayerBullet.h"
#include "../../Collision/Collider/SphereCollider.h"

Bullet::Bullet(DirectXCommon* dxCommon, std::weak_ptr<CollisionManager> collisionManager, Vector3 startPos, Vector3 shotVelocity):
 	GameObjectBase(dxCommon)
{
	//モデルのセット
	bullet = std::make_shared<ObjDraw>(*ObjDraw::Create());
	bullet->SetModel(ModelManager::GetIns()->GetModel(ModelManager::BULLET));

	//各変数の初期設定
	pos = startPos;
	velocity = shotVelocity;
	bullet->SetPos(pos);
	bullet->SetScale({ 0.5f, 0.5f, 0.5f });

	//コライダーのセット
	std::shared_ptr<SphereCollider> sphere = std::make_shared<SphereCollider>();
	sphere.get()->SetName("Bullet");
	sphere.get()->SetRadius(1.0f);
	AddCollider(sphere, collisionManager);
}

Bullet::~Bullet()
{
}

void Bullet::Init()
{

}

void Bullet::Update()
{
	//初めに現在位置を取得
	pos = bullet.get()->GetPos();
	//移動量を追加
	pos += velocity;

	//120f経過したら自動的に消去
	liveTimer++;
	if (liveTimer >= 120) {
		deleteFlag = true;
	}
}

void Bullet::Draw()
{
	//全ての処理が終わった後アップデート
	bullet->Update();
	//描画用に位置をセットし直す
	bullet->SetPos(pos);

	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();
	ObjDraw::PreDraw(cmdList);
	bullet->Draw();
	ObjDraw::PostDraw();
}

void Bullet::OnCollision(CollisionInfo info)
{
	//敵or壁に当たったら消去
 	if (info.hitName == "Enemy" || info.hitName == "Wall") {
		deleteFlag = true;
	}
}
