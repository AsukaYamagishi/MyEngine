#include "PlayerBullet.h"
#include "../../Collision/Collider/SphereCollider.h"

Bullet::Bullet(DirectXCommon* dxCommon, std::weak_ptr<CollisionManager> collisionManager, Vector3 startPos, Vector3 shotVelocity):
 	GameObjectBase(dxCommon)
{
	//���f���̃Z�b�g
	bullet = std::make_shared<ObjDraw>(*ObjDraw::Create());
	bullet->SetModel(ModelManager::GetIns()->GetModel("Bullet"));

	//�e�ϐ��̏����ݒ�
	pos = startPos;
	velocity = shotVelocity;
	bullet->SetPos(pos);
	bullet->SetScale({ 0.5f, 0.5f, 0.5f });

	//�R���C�_�[�̃Z�b�g
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
	//���߂Ɍ��݈ʒu���擾
	pos = bullet.get()->GetPos();
	//�ړ��ʂ�ǉ�
	pos += velocity;

	//120f�o�߂����玩���I�ɏ���
	liveTimer++;
	if (liveTimer >= 120) {
		deleteFlag = true;
	}
}

void Bullet::Draw()
{
	//�S�Ă̏������I�������A�b�v�f�[�g
	bullet->Update();
	//�`��p�Ɉʒu���Z�b�g������
	bullet->SetPos(pos);

	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();
	ObjDraw::PreDraw(cmdList);
	bullet->Draw();
	ObjDraw::PostDraw();
}

void Bullet::OnCollision(CollisionInfo info)
{
	//�Gor�ǂɓ������������
 	if (info.hitName == "Enemy" || info.hitName == "Wall") {
		deleteFlag = true;
	}
}
