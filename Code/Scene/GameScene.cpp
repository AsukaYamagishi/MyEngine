#include "GameScene.h"
#include "../2d/Particle/ParticleManager.h"
#include <cassert>
#include <time.h>
#include "../3d/Fbx/FbxLoader.h"
#include "../3d/Fbx/FbxDraw.h"
#include "../Wall.h"

#include "../SceneManager.h"

#include "../Collision/Collider/BaseCollider.h"

using namespace DirectX;


GameScene::GameScene(DirectXCommon* dxCommon, Audio* audio)
{
#pragma region nullptr�`�F�b�N/���
	assert(dxCommon);
	assert(audio);

	this->dxCommon = dxCommon;
	this->audio = audio;
#pragma endregion

	collisionManager = std::make_shared<CollisionManager>();
	gameObjManager = std::make_shared<GameObjectManager>(dxCommon);
	GameObjectBase::SetManager(gameObjManager);
	player = GameObjectBase::Create<PlayerBase>(dxCommon, collisionManager, PlayerType::SHOT);
	GameObjectBase::Create<EnemySpawner>(dxCommon, collisionManager, player);
	srand(time(NULL));
}

GameScene::~GameScene()
{
	//safe_delete�͂����ōs��
}

void GameScene::Init()
{
	//�J�����̂�����
	camera->Init({ 0,0,-30 });
	camera = Camera::GetCam();
#pragma endregion

#pragma region �f�o�b�O�e�L�X�g�ǂݍ���
	// �f�o�b�O�e�L�X�g�p�e�N�X�`���ǂݍ���
	if (!Sprite::LoadTexture(debugTextTexNum, L"Resources/DebugText.png")) {
		assert(0);
		return;
	}
	// �f�o�b�O�e�L�X�g������
	debugText.Init(debugTextTexNum);

#pragma endregion

#pragma region Sprite�����ݒ�
	// �e�N�X�`���ǂݍ���(�P�Ԃɂ���Ƃ悭�킩���G���[�N����)
	/*if (!Sprite::LoadTexture(3, L"Resources/white1x1.png")) {
		assert(0);
		return;
	}*/
	// �w�i�X�v���C�g����
	//spriteBG = Sprite::CreateSprite(3, { 0.0f,0.0f });
#pragma endregion
	//�f�o�C�X���Z�b�g
	FbxDraw::SetDevice(dxCommon->GetDevice());
	//�J�������Z�b�g
	FbxDraw::SetCamera(camera);
	//�O���t�B�b�N�X�p�C�v���C������
	FbxDraw::CreateGraphicsPipeline();


#pragma region 3D���f��Create�E�����ݒ�
	
	
#pragma endregion


#pragma region ���y���\�[�X�����ݒ�

	//soundData[0] = audio->SoundLoadWave("Resources/musicloop.wav");
	//audio->SoundPlayWave(audio->xAudio2.Get(), soundData[0], Audio::loop);

#pragma endregion

	/*player = new PlayerBase(PlayerType::SHOT,ModelManager::GetIns()->GetModel(ModelManager::PLAYER));
	player->Init(dxCommon);*/

	gameObjManager->Init();
	gameEndFlag = false;
}

void GameScene::Update()
{
	//�J�����̍X�V
	camera->eye.z = player->GetPos().z - 30;
	camera->target.z = camera->eye.z + 1.0f;


	if (timer % 180 == 60)
	{
		auto wall= GameObjectBase::Create<Wall>(
			Vector3{ static_cast<float>(rand() % 61 - 30),static_cast<float>(rand() % 31 - 15), player->GetPos().z + 50.0f },
			dxCommon, gameObjManager, collisionManager, player);
	}

	gameObjManager->Update();
	collisionManager->CheckHitColliders();
	camera->SetCam(camera);
	camera->Update();

#pragma region �f�o�b�O�e�L�X�g�ݒ�
	
#pragma endregion

	++timer;
}

void GameScene::Draw()
{
	// �R�}���h���X�g�̎擾
	ID3D12GraphicsCommandList *cmdList = dxCommon->GetCommandList();

#pragma region �w�i�X�v���C�g�`��
	// �w�i�X�v���C�g�`��O����
	//Sprite::PreDraw(cmdList);

	// �w�i�X�v���C�g�`��
	//spriteBG->Draw();

	// �X�v���C�g�`��㏈��
	//Sprite::PostDraw();

	//�[�x�o�b�t�@�N���A
	dxCommon->ClearDepthBuffer();
#pragma endregion

#pragma region 3D�I�u�W�F�N�g�`��
	// 3D�I�u�W�F�N�g�`��O����
	//CalculationObject::PreDraw(cmdList);


	// 3D�I�u�N�W�F�N�g�̕`��
	//object3d->Draw();


	// 3D�I�u�W�F�N�g�`��㏈��
	//CalculationObject::PostDraw();

#pragma endregion

#pragma region 3D���f���`��
	
	/*player->Draw();*/
	gameObjManager->Draw();

#pragma endregion

#pragma region �O�i�X�v���C�g�`��
	// �O�i�X�v���C�g�`��O����
	Sprite::PreDraw(cmdList);
	//�O�i�X�v���C�g�`��
	//sprite->Draw();
	// �f�o�b�O�e�L�X�g�̕`��
	debugText.DrawAll(cmdList);
	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();
#pragma endregion
}
