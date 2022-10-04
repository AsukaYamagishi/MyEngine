#pragma once
#include "../SafeDelete.h"
#include "../DirectXBase/DirectXCommon.h"
#include <DirectXMath.h>
#include "../Sprite.h"
#include "../DirectXBase/DebugText.h"
#include "../Audio/Audio.h"
#include "../KeyboardInput.h"
#include <vector>
#include "../PlayerBase.h"
#include "../Collision/Collision.h"
#include "../Model/Fbx/FbxDraw.h"
#include "../GameObject/Enemy/Boss.h"
#include "../ParticleManager.h"
#include "../Stage.h"
#include "../Manager/GameObjectManager.h"
#include "../Collision/CollisionManager.h"
#include "../Scene/AbstructScene.h"
#include "../GameObject/Enemy/EnemySpawner.h"

using namespace Microsoft::WRL;
using namespace DirectX;

//�Q�[���V�[��
class GameScene:
	public AbstructScene
{
#pragma region �ϐ�
private: //�ÓI�����o�ϐ�
	//�f�o�b�O�e�L�X�g�p�̃e�N�X�`��
	static const int debugTextTexNum = 0;

private: //�����o�ϐ�
	DirectXCommon *dxCommon = nullptr;
	Audio *audio = nullptr;
	Camera *camera = nullptr;
	DebugText debugText;
	Sprite *spriteBG;
	std::shared_ptr<GameObjectManager> gameObjManager;
	std::shared_ptr<CollisionManager> collisionManager;

	//�Q�[���V�[���p
	Sprite *sprite = nullptr;
	//���y
	Audio::SoundData soundData[3];

	//�v���C���[
	PlayerBase* player;	

	
	//�X�e�[�W
	Stage* stage;


	//FBX���f��
	std::unique_ptr<FbxModel> testModel = nullptr;
	FbxDraw *testObject = nullptr;

	std::unique_ptr<FbxModel> boxModel = nullptr;
	FbxDraw* boxObject = nullptr;

	//�p�[�e�B�N��
	ParticleManager* particleMan = nullptr;


	//�G
	//Enemy* enemy;

	float angle = 3.14f / 2.0f;

	float radius = XMConvertToRadians(2.0f);

public:
	//�Q�[���V�[���I���p
	bool gameEndFlag = false;

#pragma endregion

#pragma region �ÓI�����o�֐�

private: //�ÓI�����o�֐�
public: //�ÓI�����o�֐�
#pragma endregion

#pragma region �Q�b�^�[/�Z�b�^�[

#pragma endregion

#pragma region �����o�֐�

private: //�����o�֐�
	int timer = 0;	// �t���[����
public: //�����o�֐�
	//�R���X�g���N�^
	GameScene(DirectXCommon* dxCommon, Audio* audio);
	//�f�X�g���N�^
	~GameScene();
	//������
	void Init() override;
	//���t���[���X�V����
	void Update()override;
	//�`��
	void Draw()override;
#pragma endregion

};

